#include <stdlib.h>
#include "scheduler.h"

#define INITIAL_CAPACITY 10

Scheduler* scheduler_create_sjf(){
    Scheduler* scheduler = malloc(sizeof(Scheduler));

    if(scheduler==NULL){
        return NULL;
    }

    scheduler->processes=malloc(sizeof(Process) * INITIAL_CAPACITY);

    if (scheduler->processes==NULL){
        free(scheduler);
        return NULL;
    }

    scheduler->count=0;
    scheduler->capacity=INITIAL_CAPACITY;
    scheduler->current_index = 0;
    scheduler->quantum=0;
    scheduler->type=SCHEDULER_SJF;

    return scheduler;

} 

Process* sjf_next(Scheduler* scheduler){
    int selected_index = -1;
    int shortest_time = 0;

    for (int i = 0; i < scheduler->count; i++) {
        Process* process = &scheduler->processes[i];

        if (process->state == FINISHED) {
            continue; //bro esto salío que es una variable int, dá un IDE, y debería ser un *Process, para que ademas del IDE, dé mas datos, si me suena lógico, lo voy a cambiar xd
        }

        if (selected_index == -1 || process->burst_time < shortest_time) {
            selected_index = i;
            shortest_time = process->burst_time;
        }
    }

    if (selected_index == -1) {
        return NULL;
    }

    scheduler->processes[selected_index].state = FINISHED;

    return &scheduler->processes[selected_index];
}

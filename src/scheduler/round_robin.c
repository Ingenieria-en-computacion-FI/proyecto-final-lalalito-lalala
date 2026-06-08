#include <stdlib.h>
#include "scheduler.h"

Scheduler* scheduler_create_round_robin(int quantum)
{
    Scheduler* scheduler = malloc(sizeof(Scheduler));

    if (scheduler == NULL) {
        return NULL;
    }

    scheduler->processes = malloc(sizeof(Process) * 10);

    if (scheduler->processes == NULL) {
        free(scheduler);
        return NULL;
    }

    scheduler->count = 0;            //contador
    scheduler->capacity = 10;        //capacidad
    scheduler->current_index = 0;    //ubicación actual
    scheduler->quantum = quantum;    //cuantuym
    scheduler->type = SCHEDULER_ROUND_ROBIN;

    return scheduler;
}

Process* round_robin_next(Scheduler* scheduler) {
    if (scheduler->count == 0) {
        return NULL;
    }

    for (int attempts = 0; attempts < scheduler->count; attempts++) {
        int index = scheduler->current_index % scheduler->count;
        Process* process = &scheduler->processes[index];

        scheduler->current_index = (scheduler->current_index + 1) % scheduler->count;

        if (process->state == FINISHED) {
            continue;
        }

        process->state = RUNNING;

        if (process->remaining_time <= scheduler->quantum) {
            process->remaining_time = 0;
            process->state = FINISHED;
        } else {
            process->remaining_time -= scheduler->quantum;
            process->state = READY;
        }

        return process;
    }

    return NULL;
}
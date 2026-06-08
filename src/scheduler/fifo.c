#include <stdlib.h>
#include "scheduler.h"

#define INITIAL_CAPACITY 10

Scheduler* scheduler_create_fifo() {
    Scheduler* scheduler = malloc(sizeof(Scheduler));

    if (scheduler == NULL) {
        return NULL;
    }

    scheduler->processes = malloc(sizeof(Process) * INITIAL_CAPACITY);

    if (scheduler->processes == NULL) {
        free(scheduler);
        return NULL;
    }

    scheduler->count = 0;
    scheduler->capacity = INITIAL_CAPACITY;
    scheduler->current_index = 0;
    scheduler->quantum = 0;
    scheduler->type = SCHEDULER_FIFO;

    return scheduler;
}

Process* fifo_next(Scheduler* scheduler)
{
    while (scheduler->current_index < scheduler->count) {

        Process* process =
            &scheduler->processes[scheduler->current_index++];

        if (process->state != FINISHED) {
            process->state = FINISHED;
            return process;
        }
    }

    return NULL;
}
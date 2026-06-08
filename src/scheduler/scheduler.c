#include <stdlib.h>
#include "../../include/scheduler.h"

void scheduler_add_process(Scheduler* scheduler, Process process) {
    if (scheduler == NULL) {
        return;
    }

    if (scheduler->count >= scheduler->capacity) {
        int new_capacity = scheduler->capacity * 2;

        Process* new_processes = realloc(
            scheduler->processes,
            sizeof(Process) * new_capacity
        );

        if (new_processes == NULL) {
            return;
        }

        scheduler->processes = new_processes;
        scheduler->capacity = new_capacity;
    }

    scheduler->processes[scheduler->count] = process;
    scheduler->count++;
}

Process* scheduler_next(Scheduler* scheduler)
{
    if (scheduler == NULL) {
        return NULL;
    }

    switch (scheduler->type) {

        case SCHEDULER_FIFO:
            return fifo_next(scheduler);

        case SCHEDULER_ROUND_ROBIN:
            return round_robin_next(scheduler);

        case SCHEDULER_SJF:
            return sjf_next(scheduler);

        default:
            return NULL;
    }
}

int scheduler_is_empty(Scheduler* scheduler) {
    if (scheduler == NULL) {
        return 1;
    }

    for (int i = 0; i < scheduler->count; i++) {
        if (scheduler->processes[i].state != FINISHED) {
            return 0;
        }
    }

    return 1;
}

void scheduler_destroy(Scheduler* scheduler) {
    if (scheduler == NULL) {
        return;
    }

    free(scheduler->processes);
    free(scheduler);
}

int scheduler_has_processes(Scheduler* scheduler)  //==1, si hay procesos
{
    return !scheduler_is_empty(scheduler);
}
#include <stdlib.h>
#include "../../include/scheduler.h"

// Agrega un proceso, amplía memoria si es necesario
void scheduler_add_process(Scheduler* scheduler, Process process) {
    if (scheduler == NULL) return;

    // Duplica capacidad si el arreglo está lleno
    if (scheduler->count >= scheduler->capacity) {
        int new_capacity = scheduler->capacity * 2;
        Process* new_processes = realloc(scheduler->processes, sizeof(Process) * new_capacity);
        if (!new_processes) return;

        scheduler->processes = new_processes;
        scheduler->capacity = new_capacity;
    }

    scheduler->processes[scheduler->count] = process;
    scheduler->count++;
}

// Devuelve el siguiente proceso según el algoritmo configurado
Process* scheduler_next(Scheduler* scheduler) {
    if (!scheduler) return NULL;

    switch (scheduler->type) {
        case SCHEDULER_FIFO: return fifo_next(scheduler);
        case SCHEDULER_ROUND_ROBIN: return round_robin_next(scheduler);
        case SCHEDULER_SJF: return sjf_next(scheduler);
        default: return NULL;
    }
}

// Verifica si no hay procesos pendientes
int scheduler_is_empty(Scheduler* scheduler) {
    if (!scheduler) return 1;

    for (int i = 0; i < scheduler->count; i++) {
        if (scheduler->processes[i].state != FINISHED)
            return 0;
    }
    return 1;
}

// Libera toda la memoria del planificador
void scheduler_destroy(Scheduler* scheduler) {
    if (!scheduler) return;
    free(scheduler->processes);
    free(scheduler);
}

// Verifica si hay procesos pendientes
int scheduler_has_processes(Scheduler* scheduler) {
    return !scheduler_is_empty(scheduler);
}

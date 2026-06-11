#include <stdlib.h>
#include "scheduler.h"

#define INITIAL_CAPACITY 10  // Tamaño inicial del arreglo de procesos

// Crea e inicializa un planificador tipo FIFO
Scheduler* scheduler_create_fifo() {
    Scheduler* scheduler = malloc(sizeof(Scheduler));
    if (!scheduler) return NULL;

    // Reserva memoria para almacenar procesos
    scheduler->processes = malloc(sizeof(Process) * INITIAL_CAPACITY);
    if (!scheduler->processes) { free(scheduler); return NULL; }

    // Inicializa valores
    scheduler->count = 0;
    scheduler->capacity = INITIAL_CAPACITY;
    scheduler->current_index = 0;
    scheduler->quantum = 0;
    scheduler->type = SCHEDULER_FIFO;

    return scheduler;
}

// Obtiene el siguiente proceso según el orden de llegada
Process* fifo_next(Scheduler* scheduler) {
    while (scheduler->current_index < scheduler->count) {
        Process* process = &scheduler->processes[scheduler->current_index++];
        
        if (process->state != FINISHED) {
            process->state = FINISHED;
            return process;
        }
    }
    return NULL;  // No hay más procesos pendientes
}
``

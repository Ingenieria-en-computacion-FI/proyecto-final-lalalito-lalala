#include <stdlib.h>
#include "scheduler.h"

// Crea planificador Round Robin con el tiempo de quantum indicado
Scheduler* scheduler_create_round_robin(int quantum)
{
    Scheduler* scheduler = malloc(sizeof(Scheduler));
    if (!scheduler) return NULL;

    // Reserva memoria para hasta 10 procesos inicialmente
    scheduler->processes = malloc(sizeof(Process) * 10);
    if (!scheduler->processes) { free(scheduler); return NULL; }

    scheduler->count = 0;            // Cantidad actual de procesos
    scheduler->capacity = 10;        // Capacidad máxima inicial
    scheduler->current_index = 0;    // Posición actual en la lista
    scheduler->quantum = quantum;    // Tiempo máximo por turno
    scheduler->type = SCHEDULER_ROUND_ROBIN;

    return scheduler;
}

// Obtiene el siguiente proceso a ejecutar en orden circular
Process* round_robin_next(Scheduler* scheduler) {
    if (scheduler->count == 0) return NULL;

    // Recorre buscando un proceso activo
    for (int attempts = 0; attempts < scheduler->count; attempts++) {
        int index = scheduler->current_index % scheduler->count;
        Process* process = &scheduler->processes[index];

        scheduler->current_index = (scheduler->current_index + 1) % scheduler->count;

        if (process->state == FINISHED) continue;

        process->state = RUNNING;

        // Si termina en este turno, marca como finalizado
        if (process->remaining_time <= scheduler->quantum) {
            process->remaining_time = 0;
            process->state = FINISHED;
        } else {
            // Si no termina, reduce su tiempo y vuelve a estar listo
            process->remaining_time -= scheduler->quantum;
            process->state = READY;
        }

        return process;
    }

    return NULL; // No hay procesos pendientes
}

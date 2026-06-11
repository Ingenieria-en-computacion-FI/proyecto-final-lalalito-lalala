#include <stdlib.h>
#include "scheduler.h"

#define INITIAL_CAPACITY 10  // Capacidad inicial para procesos

// Crea e inicializa un planificador SJF (Shortest Job First)
Scheduler* scheduler_create_sjf(){
    Scheduler* scheduler = malloc(sizeof(Scheduler));
    if(!scheduler) return NULL;

    // Reserva memoria para la lista de procesos
    scheduler->processes = malloc(sizeof(Process) * INITIAL_CAPACITY);
    if (!scheduler->processes) {
        free(scheduler);
        return NULL;
    }

    scheduler->count = 0;
    scheduler->capacity = INITIAL_CAPACITY;
    scheduler->current_index = 0;
    scheduler->quantum = 0;
    scheduler->type = SCHEDULER_SJF;

    return scheduler;
}

// Selecciona el proceso con menor tiempo de ejecución
Process* sjf_next(Scheduler* scheduler) {
    if (!scheduler || scheduler->count == 0) return NULL;

    int selected_index = -1;
    int shortest_time = 999999;  // Valor inicial muy alto

    // Busca el proceso listo con menor tiempo de ráfaga
    for (int i = 0; i < scheduler->count; i++) {
        Process* process = &scheduler->processes[i];

        if (process->state == FINISHED) continue;

        if (selected_index == -1 || process->burst_time < shortest_time) {
            selected_index = i;
            shortest_time = process->burst_time;
        }
    }

    if (selected_index == -1) return NULL;

    scheduler->processes[selected_index].state = FINISHED;
    return &scheduler->processes[selected_index];
}

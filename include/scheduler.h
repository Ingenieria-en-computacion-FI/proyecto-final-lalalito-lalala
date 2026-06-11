// scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

// Tipos de algoritmos de planificación
typedef enum {
    SCHEDULER_FIFO,
    SCHEDULER_ROUND_ROBIN,
    SCHEDULER_SJF
} SchedulerType;

// Estructura del planificador
typedef struct Scheduler {
    Process* processes;   // Arreglo de procesos
    int count;            // Cantidad actual
    int capacity;         // Capacidad máxima
    int current_index;    // Índice actual
    int quantum;          // Tiempo por turno (RR)
    SchedulerType type;   // Algoritmo usado
} Scheduler;

Scheduler* scheduler_create_fifo();         // Crea planificador FIFO
Scheduler* scheduler_create_round_robin(int quantum); // Crea planificador RR
Scheduler* scheduler_create_sjf();          // Crea planificador SJF

void scheduler_add_process(Scheduler* scheduler, Process process); // Agrega proceso
Process* scheduler_next(Scheduler* scheduler); // Obtiene siguiente proceso

int scheduler_is_empty(Scheduler* scheduler);    // Verifica si está vacío
int scheduler_has_processes(Scheduler* scheduler); // Verifica si hay procesos pendientes
void scheduler_destroy(Scheduler* scheduler);    // Libera memoria

// Funciones específicas por algoritmo
Process* fifo_next(Scheduler* scheduler);
Process* round_robin_next(Scheduler* scheduler);
Process* sjf_next(Scheduler* scheduler);

#endif

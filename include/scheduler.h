//scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef enum {
    SCHEDULER_FIFO,
    SCHEDULER_ROUND_ROBIN,
    SCHEDULER_SJF
} SchedulerType;

typedef struct Scheduler {
    Process* processes;
    int count;
    int capacity;
    int current_index;
    int quantum;
    SchedulerType type;
} Scheduler;

Scheduler* scheduler_create_fifo(); //crea el planificador de fifo

Scheduler* scheduler_create_round_robin(int quantum); //planificador de round robin

Scheduler* scheduler_create_sjf(); //crea el planificador de shortest job first

void scheduler_add_process( //agrega processos a la cola
    Scheduler* scheduler,
    Process process
);

Process* scheduler_next( //devuelve el siguiente proceso según el algoritmo (FCFS, SJF, RR, etc.).
    Scheduler* scheduler
);

int scheduler_is_empty(
    Scheduler* scheduler
);

int scheduler_has_processes( //verifica si quedan procesos
    Scheduler* scheduler
);

void scheduler_destroy( //libera toda la memoria dinamica que fue reservada para ese scheluder
    Scheduler* scheduler
);

Process* fifo_next(Scheduler* scheduler);
Process* round_robin_next(Scheduler* scheduler);
Process* sjf_next(Scheduler* scheduler);

#endif
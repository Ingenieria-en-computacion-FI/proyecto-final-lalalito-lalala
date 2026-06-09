#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "process.h"

Scheduler* create_scheduler(const char* type, int quantum) {

    if (strcmp(type, "fifo") == 0) {
        return scheduler_create_fifo();
    }

    if (strcmp(type, "sjf") == 0) {
        return scheduler_create_sjf();
    }

    if (strcmp(type, "rr") == 0) {
        return scheduler_create_round_robin(quantum);
    }

    return NULL;
}

int main(int argc, char** argv) {

    if (argc < 3) {
        printf("Uso: ./main <fifo|sjf|rr> <size>\n");
        return 1;
    }

    const char* algorithm = argv[1];
    int size = atoi(argv[2]);

    int quantum = 2; // default RR quantum

    Scheduler* scheduler = create_scheduler(algorithm, quantum);

    if (scheduler == NULL) {
        printf("Algoritmo inválido\n");
        return 1;
    }

    // =========================
    // GENERAR PROCESOS
    // =========================
    for (int i = 0; i < size; i++) {

        Process p = {
            i,
            rand() % 20 + 1,
            rand() % 20 + 1,
            rand() % 5,
            rand() % 500,
            READY
        };

        scheduler_add_process(scheduler, p);
    }

    // =========================
    // EJECUCIÓN
    // =========================
    while (!scheduler_is_empty(scheduler)) {

        Process* p = scheduler_next(scheduler);

        if (p != NULL) {
            printf("PID %d ejecutado (%s)\n",
                   p->pid,
                   algorithm);
        }
    }

    scheduler_destroy(scheduler);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "process.h"
#include "process_loader.h"

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
        printf("Uso: ./main <fifo|sjf|rr> <file.csv>\n");
        return 1;
    }

    const char* algorithm = argv[1];
    const char* file = argv[2];

    int quantum = 2;

    printf("DEBUG 1\n");

    Scheduler* scheduler = create_scheduler(algorithm, quantum);

    printf("DEBUG 2\n");

    if (scheduler == NULL) {
        printf("Algoritmo inválido\n");
        return 1;
    }

    // =========================
    // CARGAR PROCESOS DESDE CSV
    // =========================

    printf("DEBUG 3\n");
    int count;
    printf("Archivo recibido: %s\n", file);
    Process* processes = load_processes(file, &count);

    printf("DEBUG 4\n");

    if (processes == NULL) {
        printf("Error leyendo archivo\n");
        return 1;
    }

    printf("DEBUG 5 count=%d\n", count);

    for (int i = 0; i < count; i++) {
    processes[i].state = READY;
    processes[i].remaining_time = processes[i].burst_time;
    scheduler_add_process(scheduler, processes[i]);
}

    free(processes);

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
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

    Scheduler* scheduler = create_scheduler(algorithm, quantum);

    if (scheduler == NULL) {
        printf("Algoritmo inválido\n");
        return 1;
    }

    // =========================
    // CARGAR PROCESOS DESDE CSV
    // =========================
    int count;
    Process* processes = load_processes(file, &count);

    if (processes == NULL) {
        printf("Error leyendo archivo\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
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
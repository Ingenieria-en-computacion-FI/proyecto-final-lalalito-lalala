#include <stdio.h>
#include <stdlib.h>
#include "process.h"

// Carga procesos desde archivo CSV y devuelve el arreglo
Process* load_processes(const char* filename, int* count) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        printf("Intentando abrir: %s\n", filename);
        return NULL;
    }

    int capacity = 100;               // Capacidad inicial
    Process* p = malloc(sizeof(Process) * capacity);
    int i = 0;

    // Lee datos: pid, tiempo, prioridad, memoria
    while (fscanf(f, "%d,%d,%d,%d",
                  &p[i].pid,
                  &p[i].burst_time,
                  &p[i].priority,
                  &p[i].memory_required) == 4) {

        // Inicializa valores de ejecución
        p[i].remaining_time = p[i].burst_time;
        p[i].state = READY;

        i++;
        // Duplica capacidad si es necesario
        if (i >= capacity) {
            capacity *= 2;
            p = realloc(p, sizeof(Process) * capacity);
        }
    }

    fclose(f);
    *count = i;  // Guarda cantidad de procesos leídos
    return p;
}

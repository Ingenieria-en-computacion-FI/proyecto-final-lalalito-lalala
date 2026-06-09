#include <stdio.h>
#include <stdlib.h>
#include "process.h"

Process* load_processes(const char* filename, int* count) {

    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    int capacity = 100;
    Process* p = malloc(sizeof(Process) * capacity);

    int i = 0;

    while (fscanf(f, "%d,%d,%d,%d",
                  &p[i].pid,
                  &p[i].burst_time,
                  &p[i].priority,
                  &p[i].memory_required) == 4) {

        // el OS lo inicializa, no Python
        p[i].remaining_time = p[i].burst_time;
        p[i].state = READY;

        i++;

        if (i >= capacity) {
            capacity *= 2;
            p = realloc(p, sizeof(Process) * capacity);
        }
    }

    fclose(f);

    *count = i;
    return p;
}
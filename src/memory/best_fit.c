#include <limits.h>
#include "memory_manager.h"
#include <stdlib.h>

/*
    BEST FIT:
    - Encuentra el bloque libre más pequeño que pueda satisfacer el tamaño
    - Retorna PID asignado o -1 si falla
*/

int best_fit(MemoryBlock* head, int size) {
    if (head == NULL || size <= 0) return -1;

    MemoryBlock* current = head;
    MemoryBlock* best = NULL;

    int min_diff = INT_MAX;

    // 1. buscar el mejor bloque
    while (current != NULL) {

        if (current->free && current->size >= size) {

            int diff = current->size - size;

            if (diff < min_diff) {
                min_diff = diff;
                best = current;
            }
        }

        current = current->next;
    }

    // 2. si no hay espacio
    if (best == NULL) return -1;

    // 3. asignar PID (temporal simple)
    static int pid_counter = 1;
    best->pid = pid_counter++;
    best->free = 0;

    int original_size = best->size;

    // 4. si sobra espacio → split
    if (original_size > size) {

        MemoryBlock* new_block = malloc(sizeof(MemoryBlock));
        if (new_block == NULL) return best->pid;

        new_block->start = best->start + size;
        new_block->size = original_size - size;
        new_block->free = 1;
        new_block->pid = -1;

        new_block->next = best->next;
        new_block->prev = best;

        if (best->next != NULL) {
            best->next->prev = new_block;
        }

        best->next = new_block;
        best->size = size;
    }

    return best->pid;
}
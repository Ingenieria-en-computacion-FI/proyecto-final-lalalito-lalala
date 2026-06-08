#include <stdlib.h>
#include "memory_manager.h"

/*
    WORST FIT:
    - Encuentra el bloque libre más grande disponible
    - Retorna PID asignado o -1 si falla
*/

int worst_fit(MemoryBlock* head, int size) {
    if (head == NULL || size <= 0) {
        return -1;
    }

    MemoryBlock* current = head;
    MemoryBlock* worst = NULL;

    int max_size = -1;

    // Buscar el bloque libre más grande
    while (current != NULL) {

        if (current->free && current->size >= size) {

            if (current->size > max_size) {
                max_size = current->size;
                worst = current;
            }
        }

        current = current->next;
    }

    // No se encontró bloque adecuado
    if (worst == NULL) {
        return -1;
    }

    // Asignar PID temporal
    static int pid_counter = 1;

    worst->pid = pid_counter++;
    worst->free = 0;

    int original_size = worst->size;

    // Dividir bloque si sobra espacio
    if (original_size > size) {

        MemoryBlock* new_block = malloc(sizeof(MemoryBlock));

        if (new_block == NULL) {
            return worst->pid;
        }

        new_block->start = worst->start + size;
        new_block->size = original_size - size;
        new_block->free = 1;
        new_block->pid = -1;

        new_block->next = worst->next;
        new_block->prev = worst;

        if (worst->next != NULL) {
            worst->next->prev = new_block;
        }

        worst->next = new_block;
        worst->size = size;
    }

    return worst->pid;
}
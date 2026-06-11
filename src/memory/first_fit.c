#include <stdlib.h>
#include "memory_manager.h"

/*
    FIRST FIT:
    - Encuentra el primer bloque libre con tamaño suficiente
    - Retorna PID asignado o -1 si no hay espacio
*/

int first_fit(MemoryBlock* head, int size) {
    if (head == NULL || size <= 0) return -1;

    MemoryBlock* current = head;

    // Recorre hasta encontrar el primer bloque adecuado
    while (current != NULL) {
        if (current->free && current->size >= size) {
            static int pid_counter = 1; // Contador de IDs únicos

            current->pid = pid_counter++;
            current->free = 0;
            int original_size = current->size;

            // Divide el bloque si sobra espacio
            if (original_size > size) {
                MemoryBlock* new_block = malloc(sizeof(MemoryBlock));
                if (!new_block) return current->pid;

                // Configura el nuevo bloque libre
                new_block->start = current->start + size;
                new_block->size = original_size - size;
                new_block->free = 1;
                new_block->pid = -1;
                new_block->next = current->next;
                new_block->prev = current;

                if (current->next) current->next->prev = new_block;
                current->next = new_block;
                current->size = size;
            }

            return current->pid;
        }
        current = current->next;
    }

    return -1; // No se encontró bloque
}


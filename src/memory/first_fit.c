#include <stdlib.h>
#include "memory_manager.h"

/*
    FIRST FIT:
    - Encuentra el primer bloque libre que pueda satisfacer el tamaño
    - Retorna PID asignado o -1 si falla
*/

int first_fit(MemoryBlock* head, int size) {
    if (head == NULL || size <= 0) {
        return -1;
    }

    MemoryBlock* current = head;

    // Buscar el primer bloque válido
    while (current != NULL) {

        if (current->free && current->size >= size) {

            static int pid_counter = 1;

            current->pid = pid_counter++;
            current->free = 0;

            int original_size = current->size;

            // Dividir bloque si sobra espacio
            if (original_size > size) {

                MemoryBlock* new_block =
                    malloc(sizeof(MemoryBlock));

                if (new_block == NULL) {
                    return current->pid;
                }

                new_block->start =
                    current->start + size;

                new_block->size =
                    original_size - size;

                new_block->free = 1;
                new_block->pid = -1;

                new_block->next =
                    current->next;

                new_block->prev =
                    current;

                if (current->next != NULL) {
                    current->next->prev =
                        new_block;
                }

                current->next = new_block;
                current->size = size;
            }

            return current->pid;
        }

        current = current->next;
    }

    return -1;
}
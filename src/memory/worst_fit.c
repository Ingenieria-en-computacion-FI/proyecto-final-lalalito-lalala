#include <stdlib.h>
#include "memory_manager.h"

/*
    WORST FIT:
    - Busca el bloque libre más grande disponible
    - Retorna el PID asignado o -1 si no hay espacio
*/

int worst_fit(MemoryBlock* head, int size) {
    if (head == NULL || size <= 0) return -1;

    MemoryBlock* current = head;
    MemoryBlock* worst = NULL;
    int max_size = -1;

    // Recorre buscando el bloque libre más grande
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size > max_size) {
                max_size = current->size;
                worst = current;
            }
        }
        current = current->next;
    }

    if (worst == NULL) return -1; // No hay bloque adecuado

    static int pid_counter = 1; // Genera ID único
    worst->pid = pid_counter++;
    worst->free = 0;
    int original_size = worst->size;

    // Divide el bloque si queda espacio libre
    if (original_size > size) {
        MemoryBlock* new_block = malloc(sizeof(MemoryBlock));
        if (!new_block) return worst->pid;

        // Configura el nuevo bloque libre
        new_block->start = worst->start + size;
        new_block->size = original_size - size;
        new_block->free = 1;
        new_block->pid = -1;
        new_block->next = worst->next;
        new_block->prev = worst;

        if (worst->next) worst->next->prev = new_block;
        worst->next = new_block;
        worst->size = size;
    }

    return worst->pid;
}

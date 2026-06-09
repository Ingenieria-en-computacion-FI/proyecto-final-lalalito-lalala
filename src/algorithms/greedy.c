#include <stdlib.h>
#include "algorithms.h"

/*
 * Divide un bloque libre y asigna memoria al proceso.
 *
 * Regresa:
 * - dirección inicial del bloque asignado si se pudo asignar
 * - -1 si no se pudo asignar
 */
static int allocate_in_block(MemoryBlock* block, int size, int pid) {
    if (block == NULL || !block->free || block->size < size || size <= 0) {
        return -1;
    }

    int start_address = block->start;

    /*
     * Si el bloque tiene exactamente el tamaño solicitado,
     * solo se marca como ocupado.
     */
    if (block->size == size) {
        block->free = 0;
        block->pid = pid;

        return start_address;
    }

    /*
     * Si el bloque es más grande, se divide en:
     *
     * [bloque ocupado][bloque libre restante]
     */
    MemoryBlock* new_block = malloc(sizeof(MemoryBlock));

    if (new_block == NULL) {
        return -1;
    }

    new_block->start = block->start + size;
    new_block->size = block->size - size;
    new_block->free = 1;
    new_block->pid = -1;

    new_block->prev = block;
    new_block->next = block->next;

    if (block->next != NULL) {
        block->next->prev = new_block;
    }

    block->next = new_block;

    block->size = size;
    block->free = 0;
    block->pid = pid;

    return start_address;
}

/*
 * FIRST FIT
 *
 * Busca el primer bloque libre donde quepa el proceso.
 */
int greedy_first_fit(MemoryManager* mm, int size, int pid) {
    if (mm == NULL || size <= 0) {
        return -1;
    }

    MemoryBlock* current = mm->head;

    while (current != NULL) {
        if (current->free && current->size >= size) {
            return allocate_in_block(current, size, pid);
        }

        current = current->next;
    }

    return -1;
}

/*
 * BEST FIT
 *
 * Busca el bloque libre más pequeño donde todavía quepa el proceso.
 * Esto intenta desperdiciar la menor cantidad posible de memoria.
 */
int greedy_best_fit(MemoryManager* mm, int size, int pid) {
    if (mm == NULL || size <= 0) {
        return -1;
    }

    MemoryBlock* current = mm->head;
    MemoryBlock* best_block = NULL;

    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (best_block == NULL || current->size < best_block->size) {
                best_block = current;
            }
        }

        current = current->next;
    }

    if (best_block == NULL) {
        return -1;
    }

    return allocate_in_block(best_block, size, pid);
}

/*
 * WORST FIT
 *
 * Busca el bloque libre más grande donde quepa el proceso.
 * Esto intenta dejar huecos grandes para futuras asignaciones.
 */
int greedy_worst_fit(MemoryManager* mm, int size, int pid) {
    if (mm == NULL || size <= 0) {
        return -1;
    }

    MemoryBlock* current = mm->head;
    MemoryBlock* worst_block = NULL;

    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (worst_block == NULL || current->size > worst_block->size) {
                worst_block = current;
            }
        }

        current = current->next;
    }

    if (worst_block == NULL) {
        return -1;
    }

    return allocate_in_block(worst_block, size, pid);
}
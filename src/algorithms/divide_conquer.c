#include <stdlib.h>
#include "algorithms.h"

/*
 * =========================================
 * DIVIDE Y VENCERÁS: MERGE SORT DE PROCESOS
 * =========================================
 *
 * Ordena un arreglo de Process* usando Merge Sort.
 * En este ejemplo se ordena por memory_required de menor a mayor.
 */

static void merge_processes(Process** array, int low, int mid, int high) {
    int left_size = mid - low + 1;
    int right_size = high - mid;

    Process** left = malloc(sizeof(Process*) * left_size);
    Process** right = malloc(sizeof(Process*) * right_size);

    if (left == NULL || right == NULL) {
        free(left);
        free(right);
        return;
    }

    for (int i = 0; i < left_size; i++) {
        left[i] = array[low + i];
    }

    for (int j = 0; j < right_size; j++) {
        right[j] = array[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = low;

    while (i < left_size && j < right_size) {
        if (left[i]->memory_required <= right[j]->memory_required) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }

        k++;
    }

    while (i < left_size) {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size) {
        array[k] = right[j];
        j++;
        k++;
    }

    free(left);
    free(right);
}

void divide_and_conquer_sort_processes(Process** array, int low, int high) {
    if (array == NULL || low >= high) {
        return;
    }

    int mid = low + (high - low) / 2;

    divide_and_conquer_sort_processes(array, low, mid);
    divide_and_conquer_sort_processes(array, mid + 1, high);

    merge_processes(array, low, mid, high);
}

/*
 * =========================================
 * DIVIDE Y VENCERÁS: COMPACTACIÓN DE MEMORIA
 * =========================================
 *
 * Mueve todos los bloques ocupados hacia el inicio de la memoria.
 * Después deja un solo bloque libre al final.
 *
 * Ejemplo visual:
 *
 * Antes:
 * [P1][Libre][P2][Libre][P3]
 *
 * Después:
 * [P1][P2][P3][Libre]
 */

void divide_and_conquer_compaction(MemoryManager* mm) {
    if (mm == NULL || mm->head == NULL) {
        return;
    }

    MemoryBlock* current = mm->head;
    MemoryBlock* new_head = NULL;
    MemoryBlock* last_allocated = NULL;

    int current_start = 0;

    /*
     * Recorremos todos los bloques.
     * Los bloques ocupados se conservan y se reacomodan.
     * Los bloques libres se eliminan.
     */
    while (current != NULL) {
        MemoryBlock* next = current->next;

        if (!current->free) {
            current->start = current_start;
            current_start += current->size;

            current->prev = last_allocated;
            current->next = NULL;

            if (last_allocated != NULL) {
                last_allocated->next = current;
            } else {
                new_head = current;
            }

            last_allocated = current;
        } else {
            free(current);
        }

        current = next;
    }

    /*
     * Si queda espacio libre, creamos un único bloque libre al final.
     */
    if (current_start < mm->total_memory) {
        MemoryBlock* free_block = malloc(sizeof(MemoryBlock));

        if (free_block == NULL) {
            mm->head = new_head;
            return;
        }

        free_block->start = current_start;
        free_block->size = mm->total_memory - current_start;
        free_block->free = 1;
        free_block->pid = -1;
        free_block->prev = last_allocated;
        free_block->next = NULL;

        if (last_allocated != NULL) {
            last_allocated->next = free_block;
        } else {
            new_head = free_block;
        }
    }

    mm->head = new_head;
}

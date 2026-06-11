#include <stdlib.h>
#include "algorithms.h"

/*
 * =========================================
 * DIVIDE Y VENCERÁS: ORDENAMIENTO
 * Ordena procesos por memoria requerida
 * =========================================
 */

// Une dos subarreglos ordenados
static void merge_processes(Process** array, int low, int mid, int high) {
    int left_size = mid - low + 1;
    int right_size = high - mid;

    // Reserva memoria para subarreglos temporales
    Process** left = malloc(sizeof(Process*) * left_size);
    Process** right = malloc(sizeof(Process*) * right_size);

    if (!left || !right) { free(left); free(right); return; }

    // Copia datos a subarreglos
    for (int i = 0; i < left_size; i++) left[i] = array[low + i];
    for (int j = 0; j < right_size; j++) right[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = low;

    // Une ordenando por tamaño de memoria
    while (i < left_size && j < right_size) {
        if (left[i]->memory_required <= right[j]->memory_required)
            array[k++] = left[i++];
        else
            array[k++] = right[j++];
    }

    // Copia elementos restantes
    while (i < left_size) array[k++] = left[i++];
    while (j < right_size) array[k++] = right[j++];

    free(left); free(right);
}

// Divide el arreglo y ordena recursivamente
void divide_and_conquer_sort_processes(Process** array, int low, int high) {
    if (!array || low >= high) return;

    int mid = low + (high - low) / 2;
    divide_and_conquer_sort_processes(array, low, mid);
    divide_and_conquer_sort_processes(array, mid + 1, high);
    merge_processes(array, low, mid, high);
}

/*
 * =========================================
 * DIVIDE Y VENCERÁS: COMPACTACIÓN
 * Reúne bloques ocupados y deja uno libre
 * =========================================
 */

void divide_and_conquer_compaction(MemoryManager* mm) {
    if (!mm || !mm->head) return;

    MemoryBlock* current = mm->head;
    MemoryBlock* new_head = NULL;
    MemoryBlock* last_allocated = NULL;
    int current_start = 0;

    // Recorre y reubica bloques ocupados
    while (current) {
        MemoryBlock* next = current->next;

        if (!current->free) {
            current->start = current_start;
            current_start += current->size;

            current->prev = last_allocated;
            current->next = NULL;

            if (last_allocated) last_allocated->next = current;
            else new_head = current;

            last_allocated = current;
        } else {
            free(current); // Elimina bloques libres dispersos
        }
        current = next;
    }

    // Crea un solo bloque libre al final si hay espacio
    if (current_start < mm->total_memory) {
        MemoryBlock* free_block = malloc(sizeof(MemoryBlock));
        if (!free_block) { mm->head = new_head; return; }

        free_block->start = current_start;
        free_block->size = mm->total_memory - current_start;
        free_block->free = 1;
        free_block->pid = -1;
        free_block->prev = last_allocated;
        free_block->next = NULL;

        if (last_allocated) last_allocated->next = free_block;
        else new_head = free_block;
    }

    mm->head = new_head;
}


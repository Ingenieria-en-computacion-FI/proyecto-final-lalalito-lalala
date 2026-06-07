#include <stdlib.h>
#include "memory_manager.h"

MemoryManager* mm_create(int total_memory)
{
    MemoryManager* mm = malloc(sizeof(MemoryManager));

    if(mm == NULL){
        return NULL;
    }

    MemoryBlock* block = malloc(sizeof(MemoryBlock));

    if(block == NULL){
        free(mm);
        return NULL;
    }

    block->start = 0;
    block->size = total_memory;
    block->free = 1;
    block->pid = -1;
    block->next = NULL;
    block->prev = NULL;

    mm->head = block;
    mm->total_memory = total_memory;

    return mm;
}

int mm_allocate_first_fit(
    MemoryManager* mm,
    int size
) {
    MemoryBlock* current = mm->head;

    while(current != NULL){

        if(current->free && current->size >= size){

            int start_address = current->start;

            /* Tamaño exacto */
            if(current->size == size){
                current->free = 0;
                return start_address;
            }

            /* Dividir bloque */
            MemoryBlock* new_block =
                malloc(sizeof(MemoryBlock));

            if(new_block == NULL){
                return -1;
            }

            new_block->start =
                current->start + size;

            new_block->size =
                current->size - size;

            new_block->free = 1;
            new_block->pid = -1;

            new_block->next = current->next;
            new_block->prev = current;

            if(current->next != NULL){
                current->next->prev = new_block;
            }

            current->next = new_block;

            current->size = size;
            current->free = 0;

            return start_address;
        }

        current = current->next;
    }

    return -1;
}

void mm_free(
    MemoryManager* mm,
    int pid
) {
    if(mm == NULL){
        return;
    }

    MemoryBlock* current = mm->head;

    while(current != NULL){

        if(current->start == pid){

            current->free = 1;
            current->pid = -1;

            mm_coalesce(mm);

            return;
        }

        current = current->next;
    }
}


void mm_destroy(
    MemoryManager* mm
) {
    if(mm == NULL){
        return;
    }

    MemoryBlock* current = mm->head;

    while(current != NULL){

        MemoryBlock* temp = current;

        current = current->next;

        free(temp);
    }

    free(mm);
}
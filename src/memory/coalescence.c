#include "memory_manager.h"
#include <stdlib.h>

void mm_coalesce(
    MemoryManager* mm
) {
    if(mm == NULL){
        return;
    }

    MemoryBlock* current = mm->head;

    while(current != NULL && current->next != NULL){

        if(current->free &&
           current->next->free){

            MemoryBlock* temp =
                current->next;

            current->size += temp->size;

            current->next = temp->next;

            if(temp->next != NULL){
                temp->next->prev = current;
            }

            free(temp);

        } else {

            current = current->next;
        }
    }
}
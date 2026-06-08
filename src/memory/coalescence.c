#include "memory_manager.h"
#include <stdlib.h>


void coalesce(MemoryBlock* head) {
    if (!head) return;

    MemoryBlock* current = head;

    while (current && current->next) {

        if (current->free && current->next->free) {

            MemoryBlock* temp = current->next;

            current->size += temp->size;
            current->next = temp->next;

            if (temp->next)
                temp->next->prev = current;

            free(temp);

            continue; //  clave
        }

        current = current->next;
    }
}
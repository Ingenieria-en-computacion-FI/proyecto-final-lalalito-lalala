#include <stdlib.h>
#include "memory_manager.h"

void mm_compact(MemoryManager* mm) {

    if (mm == NULL || mm->head == NULL) {
        return;
    }

    MemoryBlock* current = mm->head;
    int new_start = 0;

    while (current != NULL) {

        if (!current->free) {

            current->start = new_start;
            new_start += current->size;
        }

        current = current->next;
    }
}
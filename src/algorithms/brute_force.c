#include <stdlib.h>
#include "algorithms.h"
#include "../../include/algorithms.h"

/*Recorre la lista y para elejir una memoria que o : no esté ocupada y
 no sea menor al tamañano que requiere */

MemoryBlock* brute_force_find_hole(
    MemoryManager* mm,
    int required_size
) {
    if (mm == NULL || required_size <= 0) {
        return NULL;
    }

    MemoryBlock* current = mm->head;

    while (current != NULL) {

        if (current->free &&
            current->size >= required_size) {

            return current;
        }

        current = current->next;
    }

    return NULL;
}
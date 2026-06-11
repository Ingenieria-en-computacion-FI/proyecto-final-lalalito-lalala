#include <stdlib.h>
#include "memory_manager.h"

// Compacta memoria: reubica bloques ocupados al inicio
void mm_compact(MemoryManager* mm) {
    if (mm == NULL || mm->head == NULL) return;

    MemoryBlock* current = mm->head;
    int new_start = 0; // Dirección inicial para reacomodar

    while (current != NULL) {
        if (!current->free) { // Solo mueve bloques ocupados
            current->start = new_start;
            new_start += current->size;
        }
        current = current->next;
    }
}

#include "memory_manager.h"
#include <stdlib.h>

// Une bloques libres contiguos para reducir fragmentación
void coalesce(MemoryBlock* head) {
    if (!head) return;

    MemoryBlock* current = head;

    while (current && current->next) {
        // Si ambos bloques consecutivos están libres
        if (current->free && current->next->free) {
            MemoryBlock* temp = current->next;

            // Fusiona tamaños y actualiza enlaces
            current->size += temp->size;
            current->next = temp->next;
            if (temp->next) temp->next->prev = current;

            free(temp);
            continue; // Revisa de nuevo desde el bloque actual
        }
        current = current->next;
    }
}

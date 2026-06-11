#include <stdlib.h>
#include "algorithms.h"
#include "../../include/algorithms.h"

// Busca exhaustivamente el primer bloque libre con tamaño suficiente
MemoryBlock* brute_force_find_hole(
    MemoryManager* mm,
    int required_size
) {
    // Validación de entrada
    if (mm == NULL || required_size <= 0) {
        return NULL;
    }

    MemoryBlock* current = mm->head;

    // Recorre todos los bloques
    while (current != NULL) {
        // Verifica si está libre y es lo suficientemente grande
        if (current->free && current->size >= required_size) {
            return current;
        }
        current = current->next;
    }

    return NULL; // No se encontró bloque adecuado
}

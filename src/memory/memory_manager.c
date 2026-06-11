#include <stdlib.h>
#include "memory_manager.h"

// Prototipos de estrategias de asignación
int first_fit(MemoryBlock* head, int size);
int best_fit(MemoryBlock* head, int size);
int worst_fit(MemoryBlock* head, int size);

// Crea e inicializa el administrador de memoria
MemoryManager* mm_create(int total_memory) {
    if (total_memory <= 0) return NULL;

    MemoryManager* mm = malloc(sizeof(MemoryManager));
    if (!mm) return NULL;

    // Bloque inicial con toda la memoria disponible
    MemoryBlock* block = malloc(sizeof(MemoryBlock));
    if (!block) { free(mm); return NULL; }

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

// Asigna memoria usando estrategia First Fit
int mm_allocate_first_fit(MemoryManager* mm, int size) {
    if (!mm) return -1;
    return first_fit(mm->head, size);
}

// Asigna memoria usando estrategia Best Fit
int mm_allocate_best_fit(MemoryManager* mm, int size) {
    if (!mm) return -1;
    return best_fit(mm->head, size);
}

// Asigna memoria usando estrategia Worst Fit
int mm_allocate_worst_fit(MemoryManager* mm, int size) {
    if (!mm) return -1;
    return worst_fit(mm->head, size);
}

// Libera el bloque asignado a un proceso específico
void mm_free(MemoryManager* mm, int pid) {
    if (!mm) return;

    MemoryBlock* current = mm->head;
    while (current != NULL) {
        if (current->pid == pid) {
            current->free = 1;
            current->pid = -1;
            return;
        }
        current = current->next;
    }
}

// Libera toda la memoria utilizada por el administrador
void mm_destroy(MemoryManager* mm) {
    if (!mm) return;

    MemoryBlock* current = mm->head;
    while (current != NULL) {
        MemoryBlock* temp = current;
        current = current->next;
        free(temp);
    }
    free(mm);
}

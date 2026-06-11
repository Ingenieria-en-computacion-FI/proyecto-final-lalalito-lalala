// memory_manager.h
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

// Bloque de memoria
typedef struct MemoryBlock {
    int start;          // Dirección inicial
    int size;           // Tamaño del bloque
    int free;           // 1 = libre, 0 = ocupado
    int pid;            // ID del proceso asignado
    struct MemoryBlock* next;  // Bloque siguiente
    struct MemoryBlock* prev;  // Bloque anterior
} MemoryBlock;

// Administrador de memoria
typedef struct MemoryManager {
    MemoryBlock* head;  // Primer bloque
    int total_memory;   // Memoria total disponible
} MemoryManager;

MemoryManager* mm_create(int total_memory);  // Crea el administrador

int mm_allocate_first_fit(MemoryManager* mm, int size);  // Asignación First Fit
int mm_allocate_best_fit(MemoryManager* mm, int size);   // Asignación Best Fit
int mm_allocate_worst_fit(MemoryManager* mm, int size);  // Asignación Worst Fit

void mm_free(MemoryManager* mm, int pid);     // Libera memoria de un proceso
void mm_coalesce(MemoryManager* mm);           // Une bloques libres contiguos
void mm_destroy(MemoryManager* mm);             // Libera toda la estructura

#endif

// algorithms_h
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"
#include "memory_manager.h"

/* =========================================
 * 10.1 FUERZA BRUTA (brute_force.c)
 * ========================================= */
// Búsqueda exhaustiva
MemoryBlock* brute_force_find_hole(MemoryManager* mm, int required_size);


/* =========================================
 * 10.2 GREEDY (greedy.c)
 * ========================================= */
// Si tu zip tiene un greedy.c separado, la lógica de First/Best/Worst Fit 
// y SJF puede llamarse desde aquí.
int greedy_first_fit(MemoryManager* mm, int size, int pid);
int greedy_best_fit(MemoryManager* mm, int size, int pid);
int greedy_worst_fit(MemoryManager* mm, int size, int pid);


/* =========================================
 * 10.3 BACKTRACKING (backtracking.c)
 * ========================================= */
// Útil para buscar asignaciones válidas recuperando estados
int backtrack_memory_allocation(MemoryManager* mm, Process** processes, int n, int current_index);


/* =========================================
 * 10.4 DIVIDE Y VENCERÁS (divide_conquer.c)
 * ========================================= */
// Usado para reorganización o compactación de memoria
void divide_and_conquer_sort_processes(Process** array, int low, int high);
void divide_and_conquer_compaction(MemoryManager* mm);


/* =========================================
 * 10.5 PROGRAMACIÓN DINÁMICA - OPCIONAL
 * ========================================= */

// dp_bottomup.c (Ascendente)
// Ejemplo: Optimizar la cantidad de procesos que caben en un bloque
int dp_bottomup_knapsack(int memory_capacity, Process** processes, int n);

// dp_topdown.c (Descendente / Memoización)
int dp_topdown_knapsack(int memory_capacity, Process** processes, int n, int** memo);

// incremental.c (Incremental)
// Ejemplo: Recálculo de prioridades o rutas
void dp_incremental_update(Process* p, int new_factor);

#endif 
// algorithms_h
// Interfaz de algoritmos para gestión de memoria y procesos
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"         // Estructura de procesos
#include "memory_manager.h"  // Administrador de memoria

/* =========================================
 * 10.1 FUERZA BRUTA
 * Búsqueda exhaustiva de bloques libres
 * ========================================= */
// Busca un bloque de memoria del tamaño requerido revisando todos los espacios
MemoryBlock* brute_force_find_hole(MemoryManager* mm, int required_size);


/* =========================================
 * 10.2 ALGORITMOS VORACES
 * Estrategias de asignación inmediata
 * ========================================= */
// Asigna el primer bloque libre suficientemente grande
int greedy_first_fit(MemoryManager* mm, int size, int pid);

// Asigna el bloque que mejor se ajusta al tamaño solicitado
int greedy_best_fit(MemoryManager* mm, int size, int pid);

// Asigna el bloque libre más grande disponible
int greedy_worst_fit(MemoryManager* mm, int size, int pid);


/* =========================================
 * 10.3 RETROCESO
 * Prueba asignaciones y corrige si falla
 * ========================================= */
// Intenta asignar memoria a todos los procesos, retrocediendo si es necesario
int backtrack_memory_allocation(MemoryManager* mm, Process** processes, int n, int current_index);


/* =========================================
 * 10.4 DIVIDE Y VENCERÁS
 * Descompone el problema en partes más simples
 * ========================================= */
// Ordena procesos dividiendo el arreglo
void divide_and_conquer_sort_processes(Process** array, int low, int high);

// Compacta memoria reuniendo espacios libres
void divide_and_conquer_compaction(MemoryManager* mm);


/* =========================================
 * 10.5 PROGRAMACIÓN DINÁMICA - OPCIONAL
 * Reutiliza resultados para optimizar cálculos
 * ========================================= */
// Enfoque ascendente: maximiza procesos que caben en memoria
int dp_bottomup_knapsack(int memory_capacity, Process** processes, int n);

// Enfoque descendente: usa memoria para no repetir cálculos
int dp_topdown_knapsack(int memory_capacity, Process** processes, int n, int** memo);

// Actualiza datos sin recalcular todo desde cero
void dp_incremental_update(Process* p, int new_factor);

#endif

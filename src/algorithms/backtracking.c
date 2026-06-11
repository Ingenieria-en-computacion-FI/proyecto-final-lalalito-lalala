#include <stdlib.h>
#include "algorithms.h"

/* Lógica: Intentar → Asignar → Si falla, deshacer */

int backtrack_memory_allocation(
    MemoryManager* mm,
    Process** processes,
    int n,
    int current_index
) {
    // Caso base: todos los procesos asignados correctamente
    if (current_index >= n) {
        return 1;
    }

    Process* process = processes[current_index];

    // Intenta asignar memoria al proceso actual
    int pid = mm_allocate_first_fit(mm, process->memory_required);

    if (pid == -1) { // No hay espacio disponible
        return 0;
    }

    // Llama recursivamente para asignar el siguiente proceso
    if (backtrack_memory_allocation(mm, processes, n, current_index + 1)) {
        return 1;
    }

    // Retroceso: libera memoria si la asignación posterior falló
    mm_free(mm, pid);

    return 0;
}

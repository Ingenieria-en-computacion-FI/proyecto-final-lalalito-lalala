#include <stdlib.h>
#include "algorithms.h"

/*

Intentar
   ↓
Resolver siguiente
   ↓
¿Funcionó?
   ↓
Sí → éxito
No → deshacer


*/

int backtrack_memory_allocation(
    MemoryManager* mm,
    Process** processes,
    int n,
    int current_index
) {
    /* Caso base:
       Todos los procesos fueron asignados */
    if (current_index >= n) {
        return 1;
    }

    Process* process =
        processes[current_index];

    int pid = mm_allocate_first_fit(
        mm,
        process->memory_required
    );

    /* No se pudo asignar */
    if (pid == -1) {
        return 0;
    }

    /* Intentar asignar los siguientes */
    if (backtrack_memory_allocation(
            mm,
            processes,
            n,
            current_index + 1))
    {
        return 1;
    }

    /* BACKTRACK:
       deshacer la asignación actual */
    mm_free(mm, pid);

    return 0;
}
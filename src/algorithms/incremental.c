#include <stdlib.h>
#include "algorithms.h"

/*
 * PROGRAMACIÓN DINÁMICA / ACTUALIZACIÓN INCREMENTAL
 *
 * Esta función actualiza algunos valores del proceso sin recalcular
 * todo desde cero.
 *
 * En este ejemplo usamos new_factor para modificar la prioridad
 * del proceso según su estado actual.
 *
 * Regla usada:
 *
 * - Si el proceso está listo, aumenta su prioridad.
 * - Si el proceso está ejecutándose, reduce su tiempo restante.
 * - Si el proceso ya terminó, no se modifica.
 */

 //para que acaben al mismo tiempo
void dp_incremental_update(Process* p, int new_factor) {
    if (p == NULL) {
        return;
    }

    if (new_factor < 0) {
        new_factor = 0;
    }

    if (p->state == FINISHED) {
        return;
    }

    if (p->state == READY) {
        p->priority += new_factor;
    } else if (p->state == RUNNING) {
        p->remaining_time -= new_factor;

        if (p->remaining_time <= 0) {
            p->remaining_time = 0;
            p->state = FINISHED;
        }
    } else {
        p->priority += new_factor / 2;
    }
}
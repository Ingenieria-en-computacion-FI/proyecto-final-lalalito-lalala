#include <stdlib.h>
#include "algorithms.h"

/*
 * PROGRAMACIÓN DINÁMICA BOTTOM-UP
 *
 * Problema tipo mochila:
 *
 * Dada una capacidad de memoria y una lista de procesos,
 * calcula la máxima cantidad de memoria que se puede ocupar
 * sin exceder la capacidad disponible.
 *
 * Cada proceso tiene:
 * - memory_required
 *
 * En este caso usamos memory_required como:
 * - peso
 * - valor
 *
 * Es decir, buscamos aprovechar la mayor cantidad posible
 * de memoria disponible.
 *
 * Regresa:
 * - máximo uso de memoria posible
 * - -1 si hay error
 */
int dp_bottomup_knapsack(int memory_capacity, Process** processes, int n) {
    if (memory_capacity <= 0 || processes == NULL || n <= 0) {
        return -1;
    }

    /*
     * Creamos una tabla de DP de tamaño:
     *
     * (n + 1) x (memory_capacity + 1)
     *
     * dp[i][w] representa la mejor memoria aprovechada
     * usando los primeros i procesos con capacidad máxima w.
     */
    int** dp = malloc(sizeof(int*) * (n + 1));

    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = malloc(sizeof(int) * (memory_capacity + 1));

        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }

            free(dp);
            return -1;
        }
    }

    /*
     * Inicializamos toda la tabla en 0.
     */
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= memory_capacity; w++) {
            dp[i][w] = 0;
        }
    }

    /*
     * Llenado bottom-up.
     */
    for (int i = 1; i <= n; i++) {
        Process* process = processes[i - 1];

        for (int w = 0; w <= memory_capacity; w++) {
            /*
             * Si el proceso es NULL o pide memoria inválida,
             * no lo tomamos.
             */
            if (process == NULL || process->memory_required <= 0) {
                dp[i][w] = dp[i - 1][w];
            }

            /*
             * Si el proceso cabe en la capacidad actual w,
             * decidimos entre:
             *
             * 1. No tomarlo.
             * 2. Tomarlo.
             */
            else if (process->memory_required <= w) {
                int without_process = dp[i - 1][w];

                int with_process =
                    process->memory_required +
                    dp[i - 1][w - process->memory_required];

                if (with_process > without_process) {
                    dp[i][w] = with_process;
                } else {
                    dp[i][w] = without_process;
                }
            }

            /*
             * Si no cabe, heredamos la mejor solución anterior.
             */
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][memory_capacity];

    /*
     * Liberamos memoria.
     */
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }

    free(dp);

    return result;
}
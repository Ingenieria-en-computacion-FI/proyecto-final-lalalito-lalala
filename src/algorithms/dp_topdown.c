#include <stdlib.h>
#include "algorithms.h"

/*La idea más natural es modelarlo como un problema tipo Knapsack (Mochila):

Capacidad = memoria disponible.
Peso = memory_required.
Valor = priority.

Queremos:

Maximizar la suma de prioridades sin exceder la memoria disponible.*/

//-------------------------------------------------------------

/*Problema grande
↓
Subproblemas
↓
Subproblemas más pequeños*/

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

int dp_topdown_knapsack(
    int memory_capacity,
    Process** processes,
    int n,
    int** memo
)
{
    /* Caso base */
    if (n == 0 || memory_capacity <= 0) {
        return 0;
    }

    /* Ya calculado */
    if (memo[n][memory_capacity] != -1) {
        return memo[n][memory_capacity];
    }

    Process* current =
        processes[n - 1];

    /* No cabe */
    if (current->memory_required > memory_capacity) {

        memo[n][memory_capacity] =
            dp_topdown_knapsack(
                memory_capacity,
                processes,
                n - 1,
                memo
            );

        return memo[n][memory_capacity];
    }

    /* Incluir proceso */
    int include =
        current->priority +
        dp_topdown_knapsack(
            memory_capacity -
            current->memory_required,
            processes,
            n - 1,
            memo
        );

    /* Excluir proceso */
    int exclude =
        dp_topdown_knapsack(
            memory_capacity,
            processes,
            n - 1,
            memo
        );

    memo[n][memory_capacity] =
        max(include, exclude);

    return memo[n][memory_capacity];
}
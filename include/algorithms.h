//algorithms.h
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"
#include "linked_list.h"

// Algoritmos de optimización para el simulador
void solve_brute_force(Process** processes, int n);
void solve_backtracking(Process** processes, int n, int index);
void solve_divide_and_conquer(Process** processes, int low, int high);

#endif
//te parece asi emi? creo que es a lo que te referias conque estaba raro
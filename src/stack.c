// stack.c
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Nodo interno: valor y puntero al siguiente
struct Node {
    int value;
    struct Node* next;
};

// Estructura de la pila
struct Stack {
    struct Node* top; // Elemento superior
};

// Crea pila vacía
Stack* stack_create() {
    Stack* stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// Agrega elemento en la parte superior
void stack_push(Stack* stack, int value) {
    if (!stack) return;

    struct Node* new_node = malloc(sizeof(struct Node));
    if (!new_node) return;

    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
}

// Elimina y retorna el elemento superior
int stack_pop(Stack* stack) {
    if (!stack || !stack->top) return -1;

    struct Node* temp = stack->top;
    int value = temp->value;

    stack->top = temp->next;
    free(temp);
    return value;
}

// Consulta el elemento superior sin eliminarlo
int stack_peek(Stack* stack) {
    if (!stack || !stack->top) return -1;
    return stack->top->value;
}

// Verifica si la pila está vacía
int stack_is_empty(Stack* stack) {
    return (!stack || !stack->top) ? 1 : 0;
}

// Libera toda la memoria de la pila
void stack_destroy(Stack* stack) {
    if (!stack) return;
    while (!stack_is_empty(stack))
        stack_pop(stack);
    free(stack);
}

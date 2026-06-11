// stack.h
#ifndef STACK_H
#define STACK_H

typedef struct Stack Stack; // Estructura de pila

Stack* stack_create();       // Crea pila vacía
void stack_push(Stack* stack, int value); // Agrega elemento arriba
int stack_pop(Stack* stack); // Elimina y retorna el último elemento
int stack_peek(Stack* stack); // Consulta el elemento superior
int stack_is_empty(Stack* stack); // Verifica si está vacía
void stack_destroy(Stack* stack); // Libera memoria

#endif

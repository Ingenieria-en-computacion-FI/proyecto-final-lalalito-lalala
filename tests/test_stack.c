#include <stdio.h>
#include <assert.h>
#include "../include/stack.h"

void test_stack_push_pop() {

    printf("\n=== TEST STACK PUSH/POP ===\n");

    Stack* stack = stack_create();

    printf("Push(10)\n");
    stack_push(stack, 10);

    printf("Push(20)\n");
    stack_push(stack, 20);

    int value;

    value = stack_pop(stack);
    printf("Pop -> %d\n", value);
    assert(value == 20);

    value = stack_pop(stack);
    printf("Pop -> %d\n", value);
    assert(value == 10);

    stack_destroy(stack);

    printf("STACK PUSH/POP OK\n");
}

void test_stack_empty() {

    printf("\n=== TEST STACK EMPTY ===\n");

    Stack* stack = stack_create();

    printf("¿Vacía? %d\n", stack_is_empty(stack));
    assert(stack_is_empty(stack) == 1);

    printf("Push(5)\n");
    stack_push(stack, 5);

    printf("Vacia? %d\n", stack_is_empty(stack));
    assert(stack_is_empty(stack) == 0);

    stack_destroy(stack);

    printf("STACK EMPTY OK\n");
}

void test_stack_peek() {

    printf("\n=== TEST STACK PEEK ===\n");

    Stack* stack = stack_create();

    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);

    printf("Peek -> %d\n", stack_peek(stack));

    assert(stack_peek(stack) == 30);

    stack_destroy(stack);

    printf("STACK PEEK OK\n");
}

void test_stack_underflow() {

    printf("\n=== TEST STACK UNDERFLOW ===\n");

    Stack* stack = stack_create();

    int value = stack_pop(stack);

    printf("Pop pila vacía -> %d\n", value);

    assert(value == -1);

    stack_destroy(stack);

    printf("STACK UNDERFLOW OK\n");
}

int main() {

    test_stack_push_pop();

    test_stack_empty();

    test_stack_peek();

    test_stack_underflow();

    printf("\n=============================\n");
    printf("TODOS LOS TESTS PASARON\n");
    printf("=============================\n");

    return 0;
}
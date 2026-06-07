#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

struct Node {
    int value;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

Stack* stack_create() {
    Stack* stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void stack_push(Stack* stack, int value) {
    if(stack == NULL){
        return;
    }

    struct Node* new_node = malloc(sizeof(struct Node));

    if(new_node == NULL){
        return;
    }

    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
}

int stack_pop(Stack* stack) {
    if(stack==NULL||stack->top==NULL){
        return -1;
    }
    struct Node* temp = stack->top;
    int value = temp->value;

    stack->top=temp->next;

    free(temp);

    return value;
}

int stack_peek(Stack* stack) {
    if(stack==NULL||stack->top==NULL){
    return -1;
    }
    return stack->top->value;
}

int stack_is_empty(Stack* stack) {
    if(stack==NULL||stack->top==NULL){
        return 1;
    }
    return 0;
}

void stack_destroy(Stack* stack) { 
    if(stack==NULL){
        return;
    }
    while(!stack_is_empty(stack)){
        stack_pop(stack);
    }

    free(stack);
}

// queue.c
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Nodo interno: almacena valor y referencia al siguiente
typedef struct QueueNode {
    int value;
    struct QueueNode* next;
} QueueNode;

// Estructura de la cola
struct Queue {
    QueueNode* front; // Primer elemento
    QueueNode* rear;  // Último elemento
};

// Crea cola vacía
Queue* queue_create() {
    Queue* queue = malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Agrega elemento al final
void enqueue(Queue* queue, int value) {
    if (!queue) return;

    QueueNode* new_node = malloc(sizeof(QueueNode));
    if (!new_node) return;

    new_node->value = value;
    new_node->next = NULL;

    if (!queue->rear) {
        queue->front = new_node;
        queue->rear = new_node;
        return;
    }

    queue->rear->next = new_node;
    queue->rear = new_node;
}

// Elimina y retorna el primer elemento
int dequeue(Queue* queue) {
    if (!queue || !queue->front) return -1;

    QueueNode* temp = queue->front;
    int value = temp->value;

    queue->front = queue->front->next;
    if (!queue->front) queue->rear = NULL;

    free(temp);
    return value;
}

// Consulta el primer elemento sin eliminarlo
int queue_front(Queue* queue) {
    if (!queue || !queue->front) return -1;
    return queue->front->value;
}

// Verifica si la cola está vacía
int queue_is_empty(Queue* queue) {
    return (!queue || !queue->front) ? 1 : 0;
}

// Libera toda la memoria de la cola
void queue_destroy(Queue* queue) {
    if (!queue) return;
    while (!queue_is_empty(queue))
        dequeue(queue);
    free(queue);
}

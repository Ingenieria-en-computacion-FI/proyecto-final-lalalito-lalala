// circular_queue.c
#include <stdio.h>
#include <stdlib.h>
#include "circular_queue.h"

// Estructura interna de la cola circular
struct CircularQueue{
    int* data;      // Arreglo para almacenar los elementos
    int front;      // Índice del primer elemento
    int rear;       // Índice del último elemento
    int size;       // Cantidad actual de elementos
    int capacity;   // Tamaño máximo permitido
};

// Crea cola con la capacidad indicada
CircularQueue* cq_create(int capacity){
    if(capacity <= 0) return NULL;

    CircularQueue* q = malloc(sizeof(CircularQueue));
    if(!q) return NULL;

    q->data = malloc(sizeof(int) * capacity);
    if(!q->data) { free(q); return NULL; }

    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

// Agrega un elemento al final
void cq_enqueue(CircularQueue* q, int value) {
    if(!q || cq_is_full(q)) return;

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
}

// Elimina y devuelve el primer elemento
int cq_dequeue(CircularQueue* q) {
    if(!q || cq_is_empty(q)) return -1;

    int value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return value;
}

// Consulta el primer elemento sin eliminarlo
int cq_front(CircularQueue* q) {
    if(!q || cq_is_empty(q)) return -1;
    return q->data[q->front];
}

// Verifica si la cola está vacía
int cq_is_empty(CircularQueue* q) {
    return (!q || q->size == 0) ? 1 : 0;
}

// Verifica si la cola está llena
int cq_is_full(CircularQueue* q) {
    return (q && q->size == q->capacity) ? 1 : 0;
}

// Libera toda la memoria reservada
void cq_destroy(CircularQueue* q) {
    if(!q) return;
    free(q->data);
    free(q);
}

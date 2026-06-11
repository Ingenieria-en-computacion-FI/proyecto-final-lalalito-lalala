// circular_queue.h
// Interfaz de cola circular
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

// Estructura opaca de la cola
typedef struct CircularQueue CircularQueue;

// Crea cola con capacidad máxima definida
CircularQueue* cq_create(int capacity);
// Agrega un elemento al final de la cola
void cq_enqueue(CircularQueue* q, int value);
// Elimina y devuelve el elemento del frente
int cq_dequeue(CircularQueue* q);
// Devuelve el elemento del frente sin eliminarlo
int cq_front(CircularQueue* q);
// Verifica si la cola está vacía
int cq_is_empty(CircularQueue* q);
// Verifica si la cola está llena
int cq_is_full(CircularQueue* q);
// Libera la memoria de la cola
void cq_destroy(CircularQueue* q);

#endif

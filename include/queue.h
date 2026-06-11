// queue.h
#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue Queue; // Estructura de cola simple

Queue* queue_create();       // Crea cola vacía
void enqueue(Queue* queue, int value); // Agrega elemento al final
int dequeue(Queue* queue);   // Elimina y retorna el primer elemento
int queue_front(Queue* queue); // Obtiene el primer elemento sin borrarlo
int queue_is_empty(Queue* queue); // Verifica si está vacía
void queue_destroy(Queue* queue); // Libera la memoria

#endif

#include <stdio.h>
#include <stdlib.h>
#include "../include/circular_queue.h"

struct CircularQueue{
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
};

CircularQueue* cq_create(int capacity){
    if(capacity<=0){
        return NULL;
    }
    CircularQueue* q=malloc(sizeof(CircularQueue));

    if(q==NULL){
        return NULL;
    }

    q->data=malloc(sizeof(int) * capacity);

    if(q->data==NULL){
        free(q);
        return NULL;
    }

    q->front=0;
    q->rear=-1;
    q->size=0;
    q->capacity=capacity;

    return q;
}

void cq_enqueue(CircularQueue* q, int value) {
    if (q == NULL || cq_is_full(q)) {
        return;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
}

int cq_dequeue(CircularQueue* q) {
    if (q == NULL || cq_is_empty(q)) {
        return -1;
    }

    int value = q->data[q->front];

    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return value;
}

int cq_front(CircularQueue* q) {
    if (q == NULL || cq_is_empty(q)) {
        return -1;
    }

    return q->data[q->front];
}

int cq_is_empty(CircularQueue* q) {
    if (q == NULL || q->size == 0) {
        return 1;
    }

    return 0;
}

int cq_is_full(CircularQueue* q) {
    if (q == NULL) {
        return 0;
    }

    return q->size == q->capacity;
}

void cq_destroy(CircularQueue* q) {
    if (q == NULL) {
        return;
    }

    free(q->data);
    free(q);
}
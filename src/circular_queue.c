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

void cq_enqueue(CircularQueue* q, int value);
int cq_dequeue(CircularQueue* q);
int cq_front(CircularQueue* q);
int cq_is_empty(CircularQueue* q);
int cq_is_full(CircularQueue* q);
void cq_destroy(CircularQueue* q);

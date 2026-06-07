#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"

typedef struct Queue Queue{
    int value;
    struct QueueNode* next;
} QueueNode;

struct Queue{
    QueueNode* front;
    QueueNode* rear;
};

Queue* queue_create(){
    Queue* queue = malloc(sizeof(Queue));
    if(queue==NULL){
        return NULL;
    }
    queue->front=NULL;
    queue->rear=NULL;

    return queue;
}

void enqueue(Queue* queue, int value){
    if (queue == NULL) {
        return;
    }

    QueueNode* new_node = malloc(sizeof(QueueNode));

    if (new_node == NULL) {
        return;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
        return;
    }

    queue->rear->next = new_node;
    queue->rear = new_node;
}

int dequeue(Queue* queue){
    if (queue == NULL || queue->front == NULL) {
        return -1;
    }

    QueueNode* temp = queue->front;
    int value = temp->value;

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);

    return value;
}

int queue_front(Queue* queue){
    if (queue == NULL || queue->front == NULL) {
        return -1;
    }

    return queue->front->value;
}

int queue_is_empty(Queue* queue){
    if (queue == NULL || queue->front == NULL) {
        return 1;
    }

    return 0;
}

void queue_destroy(Queue* queue){
    if(queue==NULL){
        return;
    }

    while(!queue_is_empty(queue)){
        dequeue(empty);
    }
    free(queue);
}




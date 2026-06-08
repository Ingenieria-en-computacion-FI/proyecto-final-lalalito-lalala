#include <stdio.h>
#include "../include/circular_queue.h"

void test_round_robin_behavior() {

    printf("=================================\n");
    printf("TEST CIRCULAR QUEUE\n");
    printf("=================================\n\n");

    CircularQueue* q = cq_create(3);

    if (q == NULL) {
        printf("Error al crear la cola\n");
        return;
    }

    printf("Cola creada con capacidad 3\n");
    printf("¿Vacia? %d\n\n", cq_is_empty(q));

    printf("Enqueue(1)\n");
    cq_enqueue(q, 1);

    printf("Enqueue(2)\n");
    cq_enqueue(q, 2);

    printf("Enqueue(3)\n");
    cq_enqueue(q, 3);

    printf("\n");
    printf("¿Llena? %d\n", cq_is_full(q));
    printf("Front = %d\n\n", cq_front(q));

    int value;

    value = cq_dequeue(q);
    printf("Dequeue -> %d\n", value);

    printf("Enqueue(4)\n\n");
    cq_enqueue(q, 4);

    value = cq_dequeue(q);
    printf("Dequeue -> %d\n", value);

    value = cq_dequeue(q);
    printf("Dequeue -> %d\n", value);

    value = cq_dequeue(q);
    printf("Dequeue -> %d\n", value);

    printf("\n");
    printf("¿Vacia? %d\n", cq_is_empty(q));

    cq_destroy(q);

    printf("\nCola destruida correctamente\n");
}

int main() {

    test_round_robin_behavior();

    return 0;
}
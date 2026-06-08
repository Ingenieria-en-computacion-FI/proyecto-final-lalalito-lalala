#include <stdio.h>
#include <assert.h>
#include "../include/queue.h"

void test_queue_fifo() {

    printf("=================================\n");
    printf("TEST QUEUE FIFO\n");
    printf("=================================\n\n");

    Queue* queue = queue_create();

    if (queue == NULL) {
        printf("Error al crear la cola\n");
        return;
    }

    printf("Cola creada correctamente\n");
    printf("¿Vacia? %d\n\n", queue_is_empty(queue));

    printf("Enqueue(1)\n");
    enqueue(queue, 1);

    printf("Enqueue(2)\n");
    enqueue(queue, 2);

    printf("Enqueue(3)\n");
    enqueue(queue, 3);

    printf("\n");
    printf("Front = %d\n\n", queue_front(queue));

    int value;

    value = dequeue(queue);
    printf("Dequeue -> %d\n", value);

    value = dequeue(queue);
    printf("Dequeue -> %d\n", value);

    value = dequeue(queue);
    printf("Dequeue -> %d\n", value);

    printf("\n");
    printf("¿Vacia? %d\n", queue_is_empty(queue));

    printf("\nProbando dequeue en cola vacia...\n");
    printf("Resultado = %d\n", dequeue(queue));

    queue_destroy(queue);

    printf("\nCola destruida correctamente\n");
}

int main() {

    test_queue_fifo();

    return 0;
}
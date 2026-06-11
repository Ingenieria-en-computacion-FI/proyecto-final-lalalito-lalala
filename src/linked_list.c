// linked_list.c
#include <stdlib.h>
#include "linked_list.h"

// Nodo interno: valor y puntero al siguiente
typedef struct LinkedListNode {
    int value;
    struct LinkedListNode* next;
} LinkedListNode;

// Estructura de la lista simple
struct LinkedList {
    LinkedListNode* head;
};

// Crea lista vacía
LinkedList* linked_list_create() {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (!list) return NULL;
    list->head = NULL;
    return list;
}

// Inserta elemento al final
void linked_list_insert_end(LinkedList* list, int value) {
    if (!list) return;

    LinkedListNode* new_node = malloc(sizeof(LinkedListNode));
    if (!new_node) return;

    new_node->value = value;
    new_node->next = NULL;

    if (!list->head) {
        list->head = new_node;
        return;
    }

    // Recorre hasta el último nodo
    LinkedListNode* current = list->head;
    while (current->next != NULL)
        current = current->next;

    current->next = new_node;
}

// Inserta elemento al inicio
void linked_list_insert_front(LinkedList* list, int value) {
    if (!list) return;

    LinkedListNode* new_node = malloc(sizeof(LinkedListNode));
    if (!new_node) return;

    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

// Elimina y retorna el primer elemento
int linked_list_remove_front(LinkedList* list) {
    if (!list || !list->head) return -1;

    LinkedListNode* temp = list->head;
    int value = temp->value;
    list->head = list->head->next;

    free(temp);
    return value;
}

// Busca un valor, retorna 1 si existe
int linked_list_search(LinkedList* list, int value) {
    if (!list) return 0;

    LinkedListNode* current = list->head;
    while (current != NULL) {
        if (current->value == value)
            return 1;
        current = current->next;
    }
    return 0;
}

// Verifica si la lista está vacía
int linked_list_is_empty(LinkedList* list) {
    return (!list || !list->head) ? 1 : 0;
}

// Libera toda la memoria de la lista
void linked_list_destroy(LinkedList* list) {
    if (!list) return;
    while (!linked_list_is_empty(list))
        linked_list_remove_front(list);
    free(list);
}

#include <stdlib.h>
#include "doubly_linked_list.h"

// Nodo interno: almacena bloque y referencias
typedef struct DoublyLinkedListNode {
    MemoryBlock* value;
    struct DoublyLinkedListNode* next;
    struct DoublyLinkedListNode* prev;
} DoublyLinkedListNode;

// Estructura de la lista
struct DoublyLinkedList {
    DoublyLinkedListNode* head; // Primer nodo
    DoublyLinkedListNode* tail; // Último nodo
};

// Crea lista vacía
DoublyLinkedList* doubly_linked_list_create() {
    DoublyLinkedList* list = malloc(sizeof(DoublyLinkedList));
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Inserta bloque al final
void doubly_linked_list_insert_end(DoublyLinkedList* list, MemoryBlock* block) {
    if (!list) return;

    DoublyLinkedListNode* new_node = malloc(sizeof(DoublyLinkedListNode));
    if (!new_node) return;

    new_node->value = block;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (!list->tail) {
        list->head = new_node;
        list->tail = new_node;
        return;
    }

    list->tail->next = new_node;
    list->tail = new_node;
}

// Inserta bloque al inicio
void doubly_linked_list_insert_front(DoublyLinkedList* list, MemoryBlock* block) {
    if (!list) return;

    DoublyLinkedListNode* new_node = malloc(sizeof(DoublyLinkedListNode));
    if (!new_node) return;

    new_node->value = block;
    new_node->prev = NULL;
    new_node->next = list->head;

    if (!list->head) {
        list->head = new_node;
        list->tail = new_node;
        return;
    }

    list->head->prev = new_node;
    list->head = new_node;
}

// Elimina y retorna el primer bloque
MemoryBlock* doubly_linked_list_remove_front(DoublyLinkedList* list) {
    if (!list || !list->head) return NULL;

    DoublyLinkedListNode* temp = list->head;
    MemoryBlock* value = temp->value;

    list->head = list->head->next;
    if (!list->head) list->tail = NULL;
    else list->head->prev = NULL;

    free(temp);
    return value;
}

// Elimina y retorna el último bloque
MemoryBlock* doubly_linked_list_remove_back(DoublyLinkedList* list) {
    if (!list || !list->tail) return NULL;

    DoublyLinkedListNode* temp = list->tail;
    MemoryBlock* value = temp->value;

    list->tail = list->tail->prev;
    if (!list->tail) list->head = NULL;
    else list->tail->next = NULL;

    free(temp);
    return value;
}

// Busca bloque por dirección de inicio
MemoryBlock* doubly_linked_list_search(DoublyLinkedList* list, int value) {
    if (!list) return NULL;

    DoublyLinkedListNode* current = list->head;
    while (current) {
        if (current->value->start == value)
            return current->value;
        current = current->next;
    }
    return NULL;
}

// Verifica si la lista está vacía
int doubly_linked_list_is_empty(DoublyLinkedList* list) {
    return (!list || !list->head) ? 1 : 0;
}

// Libera toda la memoria de la lista
void doubly_linked_list_destroy(DoublyLinkedList* list) {
    if (!list) return;
    while (!doubly_linked_list_is_empty(list))
        doubly_linked_list_remove_front(list);
    free(list);
}

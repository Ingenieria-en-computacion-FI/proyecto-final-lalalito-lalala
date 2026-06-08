//doubly_linked_list.h
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "memory_manager.h"

// Estructura envolvente para la lista doblemente ligada
typedef struct DoublyLinkedList DoublyLinkedList;

DoublyLinkedList* doubly_linked_list_create();

// Inserción de bloques de memoria
void doubly_linked_list_insert_end(DoublyLinkedList* list, MemoryBlock* block);
void doubly_linked_list_insert_front(DoublyLinkedList* list, MemoryBlock* block);

// Remoción de bloques (útil para la administración y coalescencia)
MemoryBlock* doubly_linked_list_remove_front(DoublyLinkedList* list);
MemoryBlock* doubly_linked_list_remove_back(DoublyLinkedList* list);

// Búsqueda (por ejemplo, buscar un bloque por su dirección de inicio 'start')
MemoryBlock* doubly_linked_list_search(DoublyLinkedList* list, int start_address);

int doubly_linked_list_is_empty(DoublyLinkedList* list);

void doubly_linked_list_destroy(DoublyLinkedList* list);

#endif
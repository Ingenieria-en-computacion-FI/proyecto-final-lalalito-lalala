// doubly_linked_list.h
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "memory_manager.h"

typedef struct DoublyLinkedList DoublyLinkedList; // Estructura de lista doblemente ligada

DoublyLinkedList* doubly_linked_list_create(); // Crea lista vacía

void doubly_linked_list_insert_end(DoublyLinkedList* list, MemoryBlock* block);   // Inserta bloque al final
void doubly_linked_list_insert_front(DoublyLinkedList* list, MemoryBlock* block); // Inserta bloque al inicio

MemoryBlock* doubly_linked_list_remove_front(DoublyLinkedList* list); // Elimina y devuelve el primer bloque
MemoryBlock* doubly_linked_list_remove_back(DoublyLinkedList* list);   // Elimina y devuelve el último bloque

MemoryBlock* doubly_linked_list_search(DoublyLinkedList* list, int start_address); // Busca bloque por dirección

int doubly_linked_list_is_empty(DoublyLinkedList* list); // Verifica si está vacía
void doubly_linked_list_destroy(DoublyLinkedList* list); // Libera memoria

#endif

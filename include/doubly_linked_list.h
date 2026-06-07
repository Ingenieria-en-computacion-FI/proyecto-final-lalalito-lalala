#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct DoublyLinkedList DoublyLinkedList;

DoublyLinkedList* doubly_linked_list_create();

void doubly_linked_list_insert_end(DoublyLinkedList* list, int value);

void doubly_linked_list_insert_front(DoublyLinkedList* list, int value);

int doubly_linked_list_remove_front(DoublyLinkedList* list);

int doubly_linked_list_remove_back(DoublyLinkedList* list);

int doubly_linked_list_search(DoublyLinkedList* list, int value);

int doubly_linked_list_is_empty(DoublyLinkedList* list);

void doubly_linked_list_destroy(DoublyLinkedList* list);

#endif
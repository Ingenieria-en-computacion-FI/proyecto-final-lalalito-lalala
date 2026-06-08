//linked_list.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList LinkedList;

LinkedList* linked_list_create();

void linked_list_insert_end(LinkedList* list, int value);

void linked_list_insert_front(LinkedList* list, int value);

int linked_list_remove_front(LinkedList* list);

int linked_list_search(LinkedList* list, int value);

int linked_list_is_empty(LinkedList* list);

void linked_list_destroy(LinkedList* list);

#endif
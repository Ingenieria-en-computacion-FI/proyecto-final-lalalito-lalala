#include <stdlib.h>
#include "doubly_linked_list.h"

typedef struct DoublyLinkedListNode {
    int value;
    struct DoublyLinkedListNode* next;
    struct DoublyLinkedListNode* prev;
} DoublyLinkedListNode;

struct DoublyLinkedList {
    DoublyLinkedListNode* head;
    DoublyLinkedListNode* tail;
};

DoublyLinkedList* doubly_linked_list_create() {
    DoublyLinkedList* list = malloc(sizeof(DoublyLinkedList));

    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

void doubly_linked_list_insert_end(DoublyLinkedList* list, int value) {
    if (list == NULL) {
        return;
    }

    DoublyLinkedListNode* new_node = malloc(sizeof(DoublyLinkedListNode));

    if (new_node == NULL) {
        return;
    }

    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
        return;
    }

    list->tail->next = new_node;
    list->tail = new_node;
}

void doubly_linked_list_insert_front(DoublyLinkedList* list, int value) {
    if (list == NULL) {
        return;
    }

    DoublyLinkedListNode* new_node = malloc(sizeof(DoublyLinkedListNode));

    if (new_node == NULL) {
        return;
    }

    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = list->head;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        return;
    }

    list->head->prev = new_node;
    list->head = new_node;
}

int doubly_linked_list_remove_front(DoublyLinkedList* list) {
    if (list == NULL || list->head == NULL) {
        return -1;
    }

    DoublyLinkedListNode* temp = list->head;
    int value = temp->value;

    list->head = list->head->next;

    if (list->head == NULL) {
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }

    free(temp);

    return value;
}

int doubly_linked_list_remove_back(DoublyLinkedList* list) {
    if (list == NULL || list->tail == NULL) {
        return -1;
    }

    DoublyLinkedListNode* temp = list->tail;
    int value = temp->value;

    list->tail = list->tail->prev;

    if (list->tail == NULL) {
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }

    free(temp);

    return value;
}

int doubly_linked_list_search(DoublyLinkedList* list, int value) {
    if (list == NULL) {
        return 0;
    }

    DoublyLinkedListNode* current = list->head;

    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }

        current = current->next;
    }

    return 0;
}

int doubly_linked_list_is_empty(DoublyLinkedList* list) {
    if (list == NULL || list->head == NULL) {
        return 1;
    }

    return 0;
}

void doubly_linked_list_destroy(DoublyLinkedList* list) {
    if (list == NULL) {
        return;
    }

    while (!doubly_linked_list_is_empty(list)) {
        doubly_linked_list_remove_front(list);
    }

    free(list);
}
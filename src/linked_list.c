#include <stdlib.h>
#include "linked_list.h"

typedef struct LinkedListNode {
    int value;
    struct LinkedListNode* next;
} LinkedListNode;

struct LinkedList {
    LinkedListNode* head;
};

LinkedList* linked_list_create() {
    LinkedList* list = malloc(sizeof(LinkedList));

    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;

    return list;
}

void linked_list_insert_end(LinkedList* list, int value) {
    if (list == NULL) {
        return;
    }

    LinkedListNode* new_node = malloc(sizeof(LinkedListNode));

    if (new_node == NULL) {
        return;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        return;
    }

    LinkedListNode* current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}

void linked_list_insert_front(LinkedList* list, int value) {
    if (list == NULL) {
        return;
    }

    LinkedListNode* new_node = malloc(sizeof(LinkedListNode));

    if (new_node == NULL) {
        return;
    }

    new_node->value = value;
    new_node->next = list->head;

    list->head = new_node;
}

int linked_list_remove_front(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        return -1;
    }

    LinkedListNode* temp = list->head;
    int value = temp->value;

    list->head = list->head->next;

    free(temp);

    return value;
}

int linked_list_search(LinkedList* list, int value) {
    if (list == NULL) {
        return 0;
    }

    LinkedListNode* current = list->head;

    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }

        current = current->next;
    }

    return 0;
}

int linked_list_is_empty(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        return 1;
    }

    return 0;
}

void linked_list_destroy(LinkedList* list) {
    if (list == NULL) {
        return;
    }

    while (!linked_list_is_empty(list)) {
        linked_list_remove_front(list);
    }

    free(list);
}
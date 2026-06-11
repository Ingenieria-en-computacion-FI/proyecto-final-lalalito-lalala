// linked_list.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList LinkedList; // Estructura de lista enlazada simple

LinkedList* linked_list_create();          // Crea lista vacía
void linked_list_insert_end(LinkedList* list, int value);   // Inserta al final
void linked_list_insert_front(LinkedList* list, int value); // Inserta al inicio
int linked_list_remove_front(LinkedList* list);             // Elimina y retorna el primero
int linked_list_search(LinkedList* list, int value);        // Busca un valor
int linked_list_is_empty(LinkedList* list);                  // Verifica si está vacía
void linked_list_destroy(LinkedList* list);                  // Libera la memoria

#endif

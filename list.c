#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList()
{
  List* list = (List*) malloc(sizeof(List));

  list->head = NULL;
  list->current = NULL;
  list->tail = NULL;

  return list;
}

void* firstList(List* list)
{
  list->current = list->head;
  return list->current->data;
}

void* nextList(List* list)
{
  list->current = list->current->next;
  return list->current->data;
}

void* lastList(List* list)
{
  list->current = list->tail;
  return list->current->data;
}

void* prevList(List* list)
{
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data)
{
  Node* nuevo_nodo = (Node*) malloc(sizeof(Node));
  nuevo_nodo->data = data;
  nuevo_nodo->prev = NULL;

  nuevo_nodo->next = list->head;
  list->head->prev = nuevo_nodo;
  list->head = nuevo_nodo;
}

void pushCurrent(List * list, void* data)
{
  Node* nuevo_nodo = (Node*) malloc(sizeof(Node));
  nuevo_nodo->data = data;

  nuevo_nodo->prev = list->current;
  nuevo_nodo->next = list->current->next;
  list->current->next->prev = nuevo_nodo;
  list->current->next = nuevo_nodo;
}

void* popCurrent(List * list)
{
  Node* aux = list->current;

  aux->prev->next = aux->next;
  aux->next->prev = aux->prev;
  list->current = aux->next;

  return aux->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
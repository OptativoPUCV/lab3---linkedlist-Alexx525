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

Node * createNode(void * data){
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

void * firstList(List * list)
{
  if (list->head != NULL)
  {
    list->current = list->head;
    return list->current->data;
  }
  
  else
    return NULL;
}

void * nextList(List * list)
{
  if (list->current == NULL || list->current->next == NULL)
    return NULL;
  
  else
  {
    list->current = list->current->next;
    return list->current->data;
  }
  
}

void * lastList(List * list)
{
  if (list->tail != NULL)
  {
    list->current = list->tail;
    return list->current->data;
  }
  
  else
    return NULL;
}

void * prevList(List * list)
{
  if (list->current == NULL || list->current->prev == NULL)
    return NULL;
  
  else
  {
    list->current = list->current->prev;
    return list->current->data;
  }
}

void pushFront(List * list, void * data)
{
  Node* nuevo_nodo = (Node*) malloc(sizeof(Node));
  nuevo_nodo->data = data;
  nuevo_nodo->prev = NULL;

  if (list->head != NULL)
  {
    nuevo_nodo->next = list->head;
    list->head->prev = nuevo_nodo;
    list->head = nuevo_nodo;
  }
  
  else
  {
    list->head = nuevo_nodo;
    list->tail = nuevo_nodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data)
{
  Node* nuevo_nodo = (Node*) malloc(sizeof(Node));
  nuevo_nodo->data = data;

  if (list->current == NULL)
  {
    list->head = nuevo_nodo;
    list->tail = nuevo_nodo;
  }

  if (list->current == list->tail)
  {
    nuevo_nodo->next = NULL;
    nuevo_nodo->prev = list->current;
    list->current->next = nuevo_nodo;
    list->tail = nuevo_nodo;
  }

  else
  {
    nuevo_nodo->prev = list->current;
    nuevo_nodo->next = list->current->next;
    list->current->next->prev = nuevo_nodo;
    list->current->next = nuevo_nodo;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list)
{
  Node* aux = list->current;

  if (list->current == list->head)
  {
    list->current = list->current->next;
    list->head = list->head->next;
    list->head->prev = NULL;
    
    return aux->data;
  }

  if (list->current == list->tail)
  {
    list->current = NULL;
    list->tail->prev->next = NULL;
    list->tail = list->tail->prev;
    return aux->data;
  }

  else
  {
    list->current = aux->next;
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;

    return aux->data;
  }
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
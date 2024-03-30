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
  List* movies = (List*) malloc(sizeof(List));
  movies -> head = NULL;
  movies -> tail = NULL;

  return movies;
}

void * firstList(List * list) 
{
  if (!list -> head) return NULL;
  list -> current = list -> head;
  return (list -> current -> data);
}

void * nextList(List * list) 
{
  if (list -> head == NULL) return NULL;
  if (list -> current == NULL) return NULL;
  if (list -> current -> next == NULL) return NULL;
  list -> current = list -> current -> next;
  
  return (list -> current -> data);
}

void * lastList(List * list) 
{
  list -> current = list -> head;
  
  while (list -> current -> next != NULL)
  {
    list -> current = list -> current -> next;
  }
  
  return (list -> current -> data);
}

void * prevList(List * list) 
{
  if (list -> head == NULL ) return NULL;
  if (list -> current == NULL) return NULL;
  if (list -> current -> prev == NULL) return NULL;
  list -> current = list -> current -> prev;
 
  return (void*)(list -> current -> data);
}

void pushFront(List * list, void * data) 
{
  Node* newNode = (Node*) malloc(sizeof(Node));
  
  newNode -> data = data;
  newNode -> prev = NULL;
  newNode -> next = list -> head;

  if (list -> head) list -> head -> prev = newNode;
  list -> head = newNode;
  if (list -> tail == NULL) list -> tail = newNode;
}

void pushBack(List * list, void * data) 
{
  Node* newNode = (Node*) malloc(sizeof(Node));
  
  newNode -> data = data;
  newNode -> next = NULL;
  list -> current = list -> tail;
  newNode -> prev = list -> current;
  
  if (list -> tail) list -> tail -> next = newNode;
  list -> tail = newNode;
  if (list -> head == NULL) list -> head = newNode;
  
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
  Node* newNode = (Node*) malloc(sizeof(Node));
  newNode -> data = data;
  
  if (list -> head != NULL && list -> current != NULL)
  {
    newNode -> prev = list -> current;
    newNode -> next = list -> current -> next;

    if (list -> current -> next != NULL)
      list -> current -> next -> prev = newNode;
    else
      list -> tail = newNode;

    list -> current -> next = newNode;
  }
}

void * popFront(List * list) 
{
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) 
{
  list->current = list->tail;
  return popCurrent(list);
}

void * popCurrent(List * list) 
{
  Node* now = list -> current;
  
  if (list -> head == NULL) return NULL;
  if (list -> current == NULL) return NULL;

  if (now -> prev == NULL) list -> head = now -> next;
  else now -> prev = now -> next -> next;

  if (now -> next == NULL) list -> tail = now -> prev;
  else now -> next = now -> prev -> prev;

  return now -> data;
}

void cleanList(List * list) 
{
  while (list->head != NULL) 
  {
    popFront(list);
  }
}
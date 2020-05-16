#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dlist.h"

// constructors

dnode* dnode_create(int data, dnode* prev, dnode* next){
  dnode* current = (dnode*)malloc(sizeof(dnode));
  current->data = data;
  current->next = next;
  current->prev = prev;
  return current;
}

dlist* dlist_create(){
  struct dlist *list =  (struct dlist*)malloc(sizeof(struct dlist));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

// memeber functions

bool dlist_empty(dlist* list){ return (list->size == 0) ? true: false; }
size_t dlist_size(dlist* list){ return list->size; }

void dlist_pushfront_dnode(dlist* list, dnode* n){
  if(list->head == NULL){
    list->head = list->tail =  n;
    ++list->size;
    return;
  }
  n->next = list->head;
  list->head->prev = n;
  list->head = n;
  ++list->size;
}

void dlist_pushback_dnode(dlist* list, dnode* n){
  dnode* current = list->tail;
  if(dlist_empty(list)){
    // if empty
    list->head = list->tail = n;
  }
  else if(list->size == 1){
    // head stays the same
    // tail changes
    // tail is no longer head
    dnode* current_head = list->head;
    current_head->prev = NULL;
    current_head->next = n;
    list->tail = n;
    list->tail->next = NULL;
    list->tail->prev = list->head;
  }
  else{
    // there are two or more elements in the list
    dnode* current_tail = list->tail;
    current_tail->next = n;
    list->tail = n;
    list->tail->next = NULL;
    list->tail->prev = current_tail;
  }
  ++list->size;
}

void dlist_pushfront(dlist* list, int data){
  dnode* n = dnode_create(data, NULL, list->head);
  dlist_pushfront_dnode(list, n);
}

void dlist_pushback(dlist* list, int data){
  dnode* n = dnode_create(data, NULL, list->tail);
  dlist_pushback_dnode(list, n);
}
void dlist_popfront(dlist* list){
  if(dlist_empty(list) || list->head == NULL){ return; }
  dnode* current = list->head;
  dnode* next_ = current->next;
  list->head = next_;
  free(current);
  --list->size;
}


int dlist_front(dlist* list){ return list->head->data; }
int dlist_back(dlist* list){ return list->tail->data; }

void dlist_print(dlist* list, const char* message){
  printf("%s\n", message);
  if(dlist_empty(list)){ printf("(empty)\n"); return; }
  dnode* current = list->head;
  while(current != NULL){
    printf("%p <-- %d (%p) --> %p\n", current->prev, current->data, current, current->next);
    current = current->next;
  }
  printf("\n");
}
void dlist_popback(dlist* list){
  dnode* current = list->head;
  if(list->size == 1){ 
    free(list->head); 
    list->head = list->tail = NULL;
    --list->size; 
    return; 
  }
  while(current->next != list->tail && current->next != NULL){
    current = current->next;
  }
  free(list->tail);
  list->tail = current;
  list->tail->next = NULL;
  --list->size;
}

void dlist_clear(dlist* list, bool print){
  while(!dlist_empty(list)){
    if(print){ dlist_print(list, "clearing"); }
    dlist_popfront(list);
  }
}

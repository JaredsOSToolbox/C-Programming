#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked.h"

linked_list* linked_list_create(){
  struct linked_list *list =  (struct linked_list*)malloc(sizeof(struct linked_list));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

node* node_create(int data, node* n){
  node* p = (node*)malloc(sizeof(node));
  p->data = data;
  p->next = NULL;
  return p;
}


void linked_list_addfront_node(linked_list* list, node* n){
  // if empty
  // if one
  // if 2 or more
  n->next = list->head;
  list->head = n;
  if(list->size == 0){ list->tail = n; }
  ++list->size;
}

void linked_list_addfront(linked_list* list, int data){
  node* n = node_create(data, list->head);
  linked_list_addfront_node(list, n);
}

void linked_list_addback_node(linked_list* list, node* n){
  if(list->size == 0){ linked_list_addfront_node(list, n); return; }
  n->next = NULL;
  list->tail->next = n;
  list->tail = n;
  ++list->size;
}
void linked_list_addback(linked_list* list, int data){
  linked_list_addback_node(list, node_create(data, NULL));
}

void linked_list_print(linked_list* list){
  if(linked_list_isempty(list)){ printf("(empty)\n"); return; }
  node* p = list->head;
  while(p != NULL){
    printf("%d --> %p\n", p->data, p->next);
    p = p->next;
  }
}
int linked_list_front(linked_list* list){ return list->head->data; }
int linked_list_back(linked_list* list){ return list->tail->data; }

void linked_list_popfront(linked_list* list){
  node* p = (list->size == 1) ? NULL : list->head->next;
  free(list->head);
  list->head = p;
  --list->size;
}
void linked_list_popback(linked_list* list){
  if(list->size == 1){ 
    free(list->head); 
    list->head = NULL;
    --list->size; 
    return; 
  }
  node* p = list->head;
  while(p->next != list->tail){ p = p->next; }
  p->next = NULL;
  free(list->tail);
  list->tail = p;
  --list->size;
}

bool linked_list_isempty(linked_list* list){ return (list->size == 0) ? true : false; }
size_t linked_list_size(linked_list* list){ return list->size; }

void linked_list_clear(linked_list* list){
  while(!linked_list_isempty(list)){
    linked_list_popfront(list);
  }
}

void test(){
  linked_list* l = linked_list_create();
  for(int i = 0; i < 10; ++i){ linked_list_addfront(l, i); }
  linked_list_print(l);
  printf("top of the stack: %d\n", linked_list_front(l));
  printf("bottom of the stack: %d\n", linked_list_back(l));
  linked_list_popback(l);
  printf("bottom of the stack: %d\n", linked_list_back(l));
  linked_list_clear(l);
  linked_list_print(l);
}

int main(int argc, const char* argv[]){
  test();
  return 0;
}

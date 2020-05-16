#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked.h"
#include <assert.h>

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
  p->prev = NULL;
  return p;
}


void linked_list_addfront_node(linked_list* list, node* n){
  if(linked_list_isempty(list)){
    list->head = n;
    list->tail = NULL;
  }
  else{
    if(list->tail == NULL){
      list->tail = n;
      list->head->next = list->tail;
      list->tail->prev = list->head;
    }
    else{
      node* prev_tail = list->tail;
      n->prev = prev_tail;
      prev_tail->next = n;
      list->tail = n;
    }
  }
  ++list->size;
}

void linked_list_addfront(linked_list* list, int data){
  node* n = node_create(data, list->head);
  linked_list_addfront_node(list, n);
}

// these functions below have not yet been tested!

void linked_list_addback_node(linked_list* list, node* n){
  printf("adding back node\n");
}
void linked_list_addback(linked_list* list, int data){
  linked_list_addback_node(list, node_create(data, NULL));
}

void linked_list_print(linked_list* list){
  if(linked_list_isempty(list)){ printf("(empty)\n"); return; }
  node* p = list->head;
  printf("[");
  while(p != NULL){
    printf("%d%s", p->data, (p->next != NULL) ? " --> ": "");
    p = p->next;
  }
  printf("]\n");
}
int linked_list_front(linked_list* list){ return list->head->data; }
int linked_list_back(linked_list* list){ return list->tail->data; }

void linked_list_popfront(linked_list* list, node* n){
  /*node* p = (list->size == 1) ? NULL : list->head->next;*/
  /*free(list->head);*/
  /*list->head = p;*/
  /*--list->size;*/
  // removing the head
  printf("removing the head!\n");
  list->head = NULL;
  list->head = n->next;
  if(list->head != NULL){ list->head->prev = NULL; }
}

void linked_list_popback(linked_list* list, node* n){
  /*if(linked_list_isempty(list)){ printf("here is the error!\n"); return; }*/
  /*else if(list->size == 1){ free(list->tail); --list->size; return; }*/
  /*node* p = list->tail;*/
  /*list->tail = list->tail->prev;*/
  /*free(p);*/
  /*list->tail->next = NULL;*/
  /*--list->size;*/

  // removing the tail
  printf("removing the tail!\n");
  list->tail = NULL;
  list->tail = n->prev;
  if(list->tail != NULL){
    list->tail->next = NULL;
  }
}

bool linked_list_isempty(linked_list* list){ return (list->size == 0) ? true : false; }
size_t linked_list_size(linked_list* list){ return list->size; }

void linked_list_clear(linked_list* list){
  while(!linked_list_isempty(list)){
    linked_list_popfront(list, list->head);
  }
}

node* linked_list_find_node(linked_list* list, int data){
  node* p = list->head;
  while(p != NULL){
    if(p->data == data){ return p; }
    p = p->next;
  }
  return NULL;
}
void linked_list_remove_selected(linked_list* list, node* target){
  node* previous_node = target->prev;
  node* next_node = target->next;

  if(previous_node == NULL){
    linked_list_popfront(list, list->head);
  }

  else if(next_node == NULL){
    linked_list_popback(list, list->tail);
  }
  else{
    next_node->prev = previous_node;
    previous_node->next = next_node;
  }
  free(target);
  --list->size;
}

void test(){
  printf("running %s......\n", __func__);

  linked_list* l = linked_list_create();
  for(int i = 0; i < 10; ++i){
    linked_list_addfront(l, i);
    printf("inserting %i at the front of the list\n", i);
  }

  // printing contents of list
  printf("Content of the list: ");
  linked_list_print(l);

  // remove contents of list
  for(int i = 0; i < 10; ++i){
    linked_list_popfront(l, l->head);
    printf("Content of the list: ");
    linked_list_print(l);
  }
  printf("=====================================\n");
  // adding the contents of the list back
  for(int i = 0; i < 10; ++i){
    printf("Content of the list: ");
    linked_list_addfront(l, i);
    linked_list_print(l);
    printf("inserting %i at the front of the list\n", i);
  }
  printf("=====================================\n");

  // remove contents of the list from the back

  for(int i = 0; i < 10; ++i){
    printf("Content of the list: ");
    linked_list_print(l);
    linked_list_popback(l, l->tail);
  }
  // removing node in place

  linked_list_addfront(l, 1);

  // find node
  node* n = linked_list_find_node(l, 1);
  if(n == NULL){
    printf("test failed!\n");
  }
  else{
    linked_list_remove_selected(l, n);
  }
  printf("content of the list is: ");
  linked_list_print(l);
}

int main(int argc, const char* argv[]){
  test();
  return 0;
}

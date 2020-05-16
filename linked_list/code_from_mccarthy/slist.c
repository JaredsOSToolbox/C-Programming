#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "slist.h"

slist* slist_create(){
  struct slist *list =  (struct slist*)malloc(sizeof(struct slist));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

snode* snode_create(int data, snode* n){
  snode* p = (snode*)malloc(sizeof(snode));
  p->data = data;
  p->next = NULL;
  return p;
}


void slist_pushfront_snode(slist* list, snode* n){
  // if empty
  // if one
  // if 2 or more
  n->next = list->head;
  list->head = n;
  if(list->size == 0){ list->tail = n; }
  ++list->size;
}

void slist_pushfront(slist* list, int data){
  snode* n = snode_create(data, list->head);
  slist_pushfront_snode(list, n);
}

void slist_pushback_snode(slist* list, snode* n){
  if(list->size == 0){ slist_pushfront_snode(list, n); return; }
  n->next = NULL;
  list->tail->next = n;
  list->tail = n;
  ++list->size;
}
void slist_pushback(slist* list, int data){
  slist_pushback_snode(list, snode_create(data, NULL));
}

void slist_print(slist* list, const char* message){
  printf("%s\n", message);
  if(slist_empty(list)){ printf("(empty)\n"); return; }
  snode* p = list->head;
  while(p != NULL){
    printf("%d --> %p\n", p->data, p->next);
    p = p->next;
  }
}
int slist_front(slist* list){ return list->head->data; }
int slist_back(slist* list){ return list->tail->data; }

void slist_popfront(slist* list){
  snode* p = (list->size == 1) ? NULL : list->head->next;
  free(list->head);
  list->head = p;
  --list->size;
}
void slist_popback(slist* list){
  if(list->size == 1){ 
    free(list->head); 
    list->head = NULL;
    --list->size; 
    return; 
  }
  snode* p = list->head;
  while(p->next != list->tail){ p = p->next; }
  p->next = NULL;
  free(list->tail);
  list->tail = p;
  --list->size;
}

bool slist_empty(slist* list){ return (list->size == 0) ? true : false; }
size_t slist_size(slist* list){ return list->size; }

void slist_clear(slist* list){
  while(!slist_empty(list)){
    slist_popfront(list);
  }
}

void test(){
  slist* l = slist_create();
  for(int i = 0; i < 10; ++i){ slist_pushfront(l, i); }
  slist_print(l, "printing");
  printf("top of the stack: %d\n", slist_front(l));
  printf("bottom of the stack: %d\n", slist_back(l));
  slist_popback(l);
  printf("bottom of the stack: %d\n", slist_back(l));
  slist_clear(l);
  slist_print(l, "Printing");
}

/*int main(int argc, const char* argv[]){*/
  /*test();*/
  /*return 0;*/
/*}*/

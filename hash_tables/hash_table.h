#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HASH_TABLE_SIZ 100
#define MAX_VARS 200
#define MAX_VAR_NAME_LEN 100

// ============================================

typedef struct hash_node hash_node;
struct hash_node{
  hash_node* next;
  const char* data;
};

hash_node* hash_node_constructor(const char* word){
  hash_node* hn = (hash_node*)malloc(sizeof(hash_node));
  hn->data = strdup(word);
  return hn;
}

void hash_node_destructor(hash_node* node){ free(node); }

void hash_node_repr(hash_node* hn){
  printf("%s (%p) %s", hn->data, hn, (hn->next == NULL) ? "" : "---> ");
}

// ============================================

typedef struct hash_node_list hash_node_list;
struct hash_node_list{
  hash_node* head;
  hash_node* tail;
  size_t size;
};

hash_node_list* hash_node_list_constructor(){
  struct hash_node_list *list =  (hash_node_list*)malloc(sizeof(hash_node_list));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void hash_node_list_destructor(hash_node_list* list){
  hash_node* current = list->head;
  while(current){
    hash_node* t = current;
    current = current->next;
    hash_node_destructor(t);
  }
}

bool hash_node_list_is_empty(hash_node_list* list){ return (list->size == 0) ? true : false; }

size_t hash_node_list_size(hash_node_list* list){ return list->size; }

void hash_node_list_print(hash_node_list* list){
  hash_node* current = list->head;
  while(current != NULL){
    hash_node_repr(current);
    current = current->next;
  }
  printf("\n");
}


void hash_node_list_addfront_node(hash_node_list* list, hash_node* n){
  n->next = list->head;
  list->head = n;
  if(hash_node_list_is_empty(list)){ list->tail = n; }
  ++list->size;
}

void hash_node_list_addfront(hash_node_list* list, const char* word){
  hash_node* n = hash_node_constructor(word);
  hash_node_list_addfront_node(list, n);
}

// ==========================================

struct hash_table{
  hash_node_list** values;
  char** keys;
  int table_size_;
};

struct hash_table* new_hash_table(){
  struct hash_table* table_  = (struct hash_table*)malloc(sizeof(struct hash_table));
  table_->keys = malloc(MAX_VARS * sizeof(char*));
  table_->values = malloc(MAX_VARS * sizeof(hash_node_list*));
  for(int i = 0; i < MAX_VARS; ++i){ table_->values[i] = hash_node_list_constructor(); }
  table_->table_size_ = 0;
  return table_;
}
void hash_table_destructor(struct hash_table* map){
  free(map->keys);
  for(int i = 0; i < MAX_VARS; ++i){
    hash_node_list_destructor(map->values[i]);
  }
  free(map);
}


void insert(struct hash_table* map, char* key, char* value){
  // insert a key with a given value
  // example: (map, "JARED", 21.0)
  if(map->table_size_+1 >= HASH_TABLE_SIZ){
    fprintf(stderr, "cannot insert into the hash table, it is full\n");
    return;
  }
  map->keys[map->table_size_] = key;
  hash_node_list_addfront(map->values[map->table_size_], value);
  ++map->table_size_;
}

char* get_key(struct hash_table* map, char* key){
  // if there is a match, then return the corresponding value
  for(int i = 0; i < map->table_size_; ++i){
    if(strcmp(key, map->keys[i]) == 0){ 
      //printf("%s: %s\n", key, map->values[i]->head->data);
      return map->values[i]->head->data;
    }
  }
  return NULL;
}

void print_match(char* )


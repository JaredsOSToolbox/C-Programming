#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HASH_TABLE_SIZ 100
#define MAX_VARS 200
#define MAX_VAR_NAME_LEN 100

struct hash_table{
  double values[HASH_TABLE_SIZ];
  char** keys;
  int table_size_;
};

struct hash_table* new_hash_table(){
  struct hash_table* table_  = (struct hash_table*)malloc(sizeof(struct hash_table));
  table_->keys = malloc(MAX_VARS * sizeof(char*));
  for (int i = 0; i < MAX_VARS; i++){
    table_->keys[i] = malloc((MAX_VAR_NAME_LEN+1) * sizeof(char));
  }
  table_->table_size_ = 0;
  return table_;
}
void destructor_(struct hash_table* map){
  // free the keys table and the map itself
  for (int i = 0; i < MAX_VARS; i++){
    free(map->keys[i]);
  }
  free(map->keys);
  free(map);
}


void insert(struct hash_table* map, char* key, double value){
  // insert a key with a given value
  // example: (map, "JARED", 21.0)
  if(map->table_size_+1 >= HASH_TABLE_SIZ){
    fprintf(stderr, "cannot insert into the hash table, it is full\n");
    return;
  }
  map->keys[map->table_size_] = key;
  map->values[map->table_size_] = value;
  ++map->table_size_;
}

double get_key(struct hash_table* map, char* key){
  // if there is a match, then return the corresponding value
  // if not then complain to the console, letting user know there was an error
  for(int i = 0; i < map->table_size_; ++i){
    if(strcmp(key, map->keys[i]) == 0){ return map->values[i]; }
  }
  fprintf(stderr, "cannot retrieve key: %s, has not been set in the hash table, cowardly refusing\n", key);
  return 0.0;
}


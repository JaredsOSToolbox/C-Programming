#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/tree.h"
#include "src/file_struct.h"

bool is_noise_word(const char* list[], int i, char* pattern){
  for(int j = 0; j < i; ++j){
    if(strcmp(pattern, list[j]) == 0){ return true; }
  }
  return false;
}

void cross_reference(const char* path){
  struct file_* f_a = file_constructor(path, false);
  printf("//=========== TESTING TREE: %s =====================///\n\n", f_a->file_path);
  tree* tree = tree_create();
  const char* noise_words[BUFSIZ] = {
    "the", "and", "uh", "umm"
  };
  
  for(int i = 0; i < f_a->length; ++i){
    char* mutate = strdup(f_a->contents[i]);
    char* token = strtok(mutate, " ");
    while(token != NULL){
      if(!is_noise_word(noise_words, 4, token)){
        tree_add(tree, token, strlen(token), i+1);
      }
      token = strtok(NULL, " ");
    }
  }
  tree_print(tree);
  tree_clear(tree);
  free(tree);
  file_destructor(f_a);
}
int main(int argc, const char* argv[]) {
  if(argc < 2){
    fprintf(stderr, "Usage: %s <filename>\n", *argv++);
    return -1;
  }
  ++argv;
  cross_reference(*argv++);
  return 0;
}




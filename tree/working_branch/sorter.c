#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "src/tree.h"
#include "src/file_struct.h"

#define MAX_FREQ 200

bool is_noise(const char* word[], char* pattern, int n){
  for(int i = 0; i < n; ++i){
    if(strcmp(pattern, word[i]) == 0){ return true; }
  }
  return false;
}
void sorter(const char* path){
  struct file_* f_a = file_constructor(path, false);
  printf("//=========== TESTING TREE: %s =====================///\n\n", f_a->file_path);
  tree* tree = tree_create();
  const char* noise_words[BUFSIZ] = {
    "the", "and", "uh", "umm"
  };

  
  for(int i = 0; i < f_a->length; ++i){
    char* mutate = strdup(f_a->contents[i]);
    char* token = strtok(mutate, " ");
    while(token != NULL && !is_noise(noise_words, token, 4)){
      tree_add(tree, token, strlen(token), i+1);
      token = strtok(NULL, " ");
    }
  }

  struct tree* trees_freq[BUFSIZ];
  memset(trees_freq, 0, MAX_FREQ * sizeof(struct tree*));
  treefreq_fromtree(trees_freq, tree);

  treefreq_print(trees_freq, MAX_FREQ);
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
  sorter(*argv++);
  return 0;
}

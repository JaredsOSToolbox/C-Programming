#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_replace.h"

void detab_(char *content, size_t n_){
  find_replace_print_(content, ' ', '\t', n_);
}

int main(int argc, const char* argv[]){
  int amount;
  if(argc < 2){
    amount = TAB_SIZE;
  } else{
    amount = atoi(argv[1]);
  }

  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, stdin)) != EOF) {
    detab_(line, amount);
  }
  free(line);
  return 0;
}

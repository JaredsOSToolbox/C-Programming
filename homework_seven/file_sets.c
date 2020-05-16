#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "includes/file_struct.h"
#include "includes/delta.h"

#define MAX_FILE_AMOUNT 10

int main(int argc, const char* argv[]){
  if(argc < 3 || argc > MAX_FILE_AMOUNT+1){
    fprintf(stderr, "Usage: %s <file 1> <file 2>\n", *argv);
    return -1;
  }
  ++argv; --argc;
  const char* title = strdup(*argv++); --argc;
  int page_count = 0;
  struct file_* file_set[MAX_FILE_AMOUNT];
  while(argc-- > 0){
    file_set[page_count++] = file_constructor(*argv++);
  }

  printf("TITLE: %s\n\n\n", title);

  for(int i = 0; i < page_count; ++i){
    printf("%s\n===================\n", file_set[i]->file_path);
    print_contents_normal(stdout, file_set[i]);
    printf("\t\t(%d/%d)\n", i, page_count-1);
    printf("=================================\n");
    file_destructor(file_set[i]);
  }
  return 0;
}

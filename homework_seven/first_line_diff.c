#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "includes/file_struct.h"
#include "includes/delta.h"

int main(int argc, const char* argv[]){
  if(argc < 2 || argc > 3){
    fprintf(stderr, "Usage: %s <file 1> <file 2>\n", *argv);
    return -1;
  }
  ++argv;
  char* message = (char*)malloc(FNEQ_MES_LEN*sizeof(char));
  struct file_* a = file_constructor(*argv++);
  struct file_* b = file_constructor(*argv++);
  if(!compare_contents(a, b, message)){
    printf("%s", message);
  } else{
    printf("Files %s and %s are identical\n", a->file_path, b->file_path);
  }
  free(message);
  file_destructor(a);
  file_destructor(b);
}

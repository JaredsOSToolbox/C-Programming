#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]){
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_number_ = 0;
  while ((read = getline(&line, &len, stdin)) != EOF) {
    printf("[%d] %s", ++line_number_, line);
  }
  free(line);
  return 0;
}

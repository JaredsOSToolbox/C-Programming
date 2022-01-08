#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LINE_COUNT 10

int main(int argc, const char* argv[]){
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_number_ = 1;
  int n_;
  if(argc < 2){
    n_ = LINE_COUNT;
  } else{ 
    n_ = atoi(argv[1]);
  }

  while ((read = getline(&line, &len, stdin)) != EOF && n_-- > 0) {
    printf("[%d] %s", line_number_++, line);
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LINE_COUNT 10

int main(int argc, const char* argv[]){
  char *lines[BUFSIZ];
  size_t len = 0;
  ssize_t read;
  int line_number_ = 1;
  int n_;

  if(argc < 2){
    n_ = LINE_COUNT;
  } else{ 
    n_ = atoi(argv[1]);
  }

  while ((read = getline(&lines[line_number_], &len, stdin)) != EOF) {
    ++line_number_;
  }
  for(int i = (n_ > line_number_) ? 1 : abs(n_ - line_number_); i < line_number_; ++i){
      printf("[%d] %s", i, lines[i]);
  }
  return 0;
}

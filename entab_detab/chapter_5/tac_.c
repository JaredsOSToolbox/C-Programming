#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, const char* argv[]){
  char *lines[BUFSIZ];
  size_t len = 0;
  ssize_t read;
  int line_number_ = 1;

  while ((read = getline(&lines[line_number_], &len, stdin)) != EOF) {
    ++line_number_;
  }
  for(int i = line_number_; i >= 1; --i){
      printf("%s", lines[i]);
  }
  return 0;
}

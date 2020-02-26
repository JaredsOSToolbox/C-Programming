#include <stdio.h>
#include "binary_converter.h"

void test_input(int input){
  fprintf(stdout, "%d\n", input);
}

int main(int argc, const char* argv[]){
  char str[] = "11A";
  for(int i = 0; i <= 16; ++i){
    fprintf(stdout, "Base: %d, Original: %s, Repr: %d\n", i, str, to_base_n(str, i));
  }
  return 0;
}

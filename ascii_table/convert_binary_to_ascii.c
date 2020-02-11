#include <stdio.h>
#include <stdlib.h>
#include "binary_converter.h"

int main(int argc, const char* argv[]){
  if(argc != 3){
    fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
    exit(1);
  }
  FILE* in = fopen(argv[1], "r");
  FILE* out = fopen(argv[2], "w");

  process_file(in, out);
  fclose(in);
  fclose(out);

  return 0;
}

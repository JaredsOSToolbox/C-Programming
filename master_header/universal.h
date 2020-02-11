#include <stdio.h>


void cat(FILE* in, FILE* out){
  char c;
  while((c = fgetc(in)) != EOF){
    fputc(c, out);
  }
}

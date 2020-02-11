#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../master_header/universal.h"

#define IN true
#define OUT false

void parse(int value, FILE* out){
  const char table[] = {'A', 'B', 'C', 'D', 'E', 'F'};
  int base = 10;

  if(value >= 10 && value <= 16){
    int index = (value - base)-1;
    if(index >= 0){  
      fprintf(out, "%c\n", table[index]);
    }
  }
  else{
    fprintf(out, "%d\n", value);
  }
}

int main(int argc, const char* argv[]){
  FILE* output = fopen("hex_output", "w");
  for(int i = 0; i < 17; ++i){
    parse(i, output);
  }
  fclose(output);
  output = fopen("hex_output", "r");
  cat(output, stdout);
  fclose(output);
  return 0;
}

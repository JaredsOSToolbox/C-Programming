#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../master_header/universal.h"

#define IN true
#define OUT false

char hex_parser(int value){
  int base = 10;
  int index = (value - base)-1;

  if(value >= 10 && value <= 16){
    return (index >= 0) ? (char)(index+65) : '\0';
  }
  return (char)(value+48);
}

int main(int argc, const char* argv[]){
  for(int i = 0; i < 17; ++i){
    fprintf(stdout, "%c\n", hex_parser(i));
  }
  return 0;
}

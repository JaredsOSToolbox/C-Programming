#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN true
#define OUT false
#define TAB_SIZE 4

void n_printf_(char c, size_t s){ for(int i = 0; i < s; ++i){ printf("%c", c); } }

void find_replace_print_(char *content, char pattern, char delimiter, size_t n_){
  bool state_ = OUT;
  while(*content != '\0'){
    if(*content == delimiter){
      n_printf_(pattern, n_);
    } else if(isalpha(*content)){
      state_ = IN;
      printf("%c", *content);
    } else{
      state_ = OUT;
    }
    *content++;
  }
  printf("\n");
}

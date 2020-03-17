#include <stdio.h>
#include <string.h>

int strcmp_(const char* a, const char* b){
  while((*a != '\0') && (*a++ == *b++)){}
  return (*a - *b);
}

int main(){
  fprintf(stdout, "output of strcmp_: %d\n", strcmp_("Hello World", "Hello"));
  return 0;
}

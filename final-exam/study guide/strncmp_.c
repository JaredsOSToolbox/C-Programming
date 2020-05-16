#include <stdio.h>
#include <assert.h>
#include <string.h>

int strncmp_(const char* a, const char* b, size_t n){
  while((*a != '\0') && (*a++ == *b++) && (--n > 0)){}
  return (n == 0) ? n : (*a - *b);
}

void asserts(){
  assert(strncmp_("Hello", "Hello World", 5) == strncmp("Hello", "Hello World", 5));
}

int main(){
  asserts();
  return 0;
}

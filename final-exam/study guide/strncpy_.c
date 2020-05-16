#include <string.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

char* strncpy_(char* dest, const char* src, size_t n){
  char* ptr = dest;
  while((*ptr++ = *src++) && (*src != '\0') && (--n > 0)){}
  *ptr = '\0';
  return dest;
}

void asserts(){
  char buffer[BUFSIZ];
  char buffer_two[BUFSIZ];
  const char* message = "Hello World";
  assert((strcmp(strncpy_(buffer, message, 5), "Hello") == 0) == 
          (strcmp(strncpy(buffer_two, message, 5), "Hello") == 0));
}

int main(int argc, const char* argv[]){
  asserts();
  return 0;
}

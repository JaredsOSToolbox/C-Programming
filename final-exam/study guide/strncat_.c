#include <stdio.h>
#include <string.h>
#include <assert.h>

char* strncat_(char* dest, const char* src, size_t n){
  char* ptr = dest + strlen(dest);
  while((*ptr++ = *src++) && (*src != '\0') && (--n > 0)){}
  *ptr = '\0';
  return dest;
}


void asserts(){
  char buffer[BUFSIZ] = "To infinity";
  char buffer_two[BUFSIZ] = "To infinity";
  const char* message = " and beyond!";
  const char* full_message = "To infinity and beyond!";

  assert((strcmp(strncat_(buffer, message, 12), full_message)) == 
          (strcmp(strncat(buffer_two, message, 12), full_message)));
}

int main(){
  asserts();
  return 0;
}

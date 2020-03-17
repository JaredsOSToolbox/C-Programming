#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strcat_(char* destination, char* source){
  char* ptr = destination + strlen(destination);
  while((*ptr++ = *source++) && (*source != '\0')){}
  *ptr = '\0';
  return destination;
}

void test_strcat_(char* destination, char* source, char* outcome){
  char dest[BUFSIZ];
  strcpy(dest, destination);
  strcat_(dest, source);
  assert(strcmp(dest, outcome) == 0);
}

int main(int argc, const char* argv[]){
  test_strcat_("Hello", "World", "HelloWorld");
  return 0;
}

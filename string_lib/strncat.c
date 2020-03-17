#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strncat_(char* destination, char* source, size_t n){
  char* ptr = destination + strlen(destination);
  while((*ptr++ = *source++) && (*source != '\0') && (--n > 0)){}
  *ptr = '\0';
  return destination;
}

int main(int argc, const char* argv[]){
  char destination[30];
  strcpy(destination, "Hello");
  char source[] = "World This";
  fprintf(stdout, "contents of t: %s\n", strncat_(destination, source, 5));
  return 0;
}

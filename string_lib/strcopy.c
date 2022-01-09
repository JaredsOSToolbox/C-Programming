#include <stdio.h>
#include <string.h>

char* strcopy(char* destination, char* source) {
  /*if(strlen(source) > strlen(destination)){*/
  /*fprintf(stderr, "size mismatch!\n");*/
  /*return NULL;*/
  /*}*/
  for (int i = 0; i < strlen(source) && source[i] != '\0'; ++i) {
    destination[i] = source[i];
  }
  return destination;
}

int main(int argc, const char* argv[]) {
  char* s = "Hello World";
  char d[100];
  strcopy(d, s);
  fprintf(stdout, "contents of d: %s\n", d);
  return 0;
}

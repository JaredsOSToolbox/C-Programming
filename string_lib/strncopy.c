#include <stdio.h>
#include <string.h>

void strncpy_(char* destination, char* source, size_t n) {
  while ((*destination++ = *source++) && --n > 0) {
  }
}

int main(int argc, const char* argv[]) {
  char* s = "Hello World";
  char d[10];
  memset(d, 0, sizeof(char) * 10);
  strncpy_(d, s, 5);
  fprintf(stdout, "contents of d: %s\n", d);
  return 0;
}

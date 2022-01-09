#include <stdio.h>

char *strchr_(const char *s, int c) {
  while ((*s != (char)c) && *s++ != '\0') {
  }
  return (char *)s;
}

int main() {
  char pattern = 'b';
  char string[] = "abc";
  printf("%s\n", strchr_(string, pattern));
  /*printf("%s\n", example("Hello", 'H'));*/
  return 0;
}

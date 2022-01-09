#include <stdio.h>

char *strrchr_(char *s, int c) {
  char *ptr = NULL;
  do {
    if (*s == (char)c) {
      ptr = s;
    }
  } while (*s++);
  return ptr;
}

int main() {
  char pattern = 'b';
  char string[] = "abcbr";
  printf("%s\n", strrchr_(string, pattern));
  return 0;
}

#include <stdio.h>
#include <string.h>

int strncmp_(const char* a, const char* b, size_t n) {
  while ((*a != '\0') && (*a++ == *b++) && (--n > 0)) {
  }
  if (*a - *b > 0) {
    return 1;
  } else if (*a - *b < 0) {
    return -1;
  }
  return 0;
}

int main() {
  const char a[] = "Hello";
  const char b[] = "Hello";
  int result = strncmp_(a, b, strlen(a));
  if (result == 0) {
    printf("match!\n");
  } else if (result > 0) {
    printf("b is bigger than a!\n");
  } else {
    printf("b is smaller than a\n");
  }
  return 0;
}

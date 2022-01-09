#include <assert.h>
#include <stdio.h>
#include <string.h>

size_t strlen_(char* s) {
  size_t c = 0;
  while (*s++ != '\0') {
    ++c;
  }
  return c;
}

void asserts() { assert(strlen_("Hello") == strlen("Hello")); }

int main() {
  asserts();
  return 0;
}

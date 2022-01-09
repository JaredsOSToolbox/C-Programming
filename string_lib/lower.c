#include <ctype.h>
#include <stdio.h>
#include <string.h>

void lower_(char* string) {
  while (*string != '\0') {
    if (isalpha(*string)) {
      string = tolower(*string++);
    } else {
      string++;
    }
  }
}

int main() {
  char message[] = "HELLO WORLD!";
  lower_(message);
  printf("%s\n", message);
  return 0;
}

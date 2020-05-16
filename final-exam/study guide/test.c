#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(){
  /*char buf[] = "-n";*/
  /*bool n = strstr(buf, "-n") != NULL;*/
  /*printf("n: %s", (n) ? "true" : "false");*/


  const char* buf = "Hello";
  const char* rejection = "Hello World";
  size_t amount = strcspn(buf, rejection);
  printf("%zu\n", amount);
  return 0;
}

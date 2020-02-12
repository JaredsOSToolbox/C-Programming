#include <stdio.h>
#include "universal.h"

int main(int argc, const char* argv[]){
  FILE* in = fopen("/tmp/example", "r");
  wc_(in, stdout);
  return 0;
}

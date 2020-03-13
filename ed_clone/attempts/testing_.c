// TEST CODE
#include "ed_headers.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

bool console_flag = false;

int main(int argc, const char* argv[]){
  if(argc < 2){ fprintf(stderr, "Usage: %s [pattern] [file(s)]\n", argv[0]); }
  /*argv++;*/
  /*while(argc > 1 && **argv == '-'){*/
    /*switch((*argv)[1]){*/
      /*case '\0': console_flag = true; break;*/
      /*case 'r': printf("r flag\n"); break;*/
    /*}*/
    /*argv++;*/
    /*argc--;*/
  /*}*/
  /*mkstemp("/tmp/tempfile");*/
  /*unlink("/tmp/tempfile");*/
  compile();
  return 0;
}

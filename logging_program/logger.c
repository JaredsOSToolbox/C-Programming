#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// is the file open?
// we need to pass in file descriptor so we can properly close it
// if NULL <- file is not open
// else <- file is open

bool open_file(FILE* input){ return (input != NULL); }

int main(int argc, const char* argv[]){
  return 0;
}

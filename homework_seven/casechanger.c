#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char toupper_(char c){ return (char)(c-32); }
char tolower_(char c){ return (char)(c+32); }

bool upper = false, lower = false;

void set_args(const char* fed_in, const char* small, const char* long_v, bool* flag){
  if(strcmp(fed_in, small) == 0 || ((long_v) && strcmp(fed_in, long_v) == 0)){
    *flag = true;
  }
}
void process_args(int argc, const char* argv[]){
  while(argc-- > 0){
    set_args(*argv, "-u", "--upper", &upper);
    set_args(*argv, "-l", "--lower", &lower);
    ++argv;
  }
}

int main(int argc, const char* argv[]){
  if(argc < 2 || argc > 3){
    fprintf(stderr, "Usage: %s <flag> <string>\n", *argv);
    return -1;
  }
  char* buffer = strdup(argv[2]);
  process_args(--argc, ++argv);
  char c;
  for(size_t i = 0; i < strlen(buffer); ++i){
    c = buffer[i];
    if(!isalpha(c)){ continue; }
    if(lower && isupper(c)){
      buffer[i] = tolower(c);
    } else if(upper && islower(c)){
      buffer[i] = toupper(c);
    }
  }
  printf("Value of buffer is: %s\n", buffer);
  return 0; 
}

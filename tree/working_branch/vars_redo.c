#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/file_struct.h"
#include "src/tree.h"
#include "src/dlist.h"

bool is_multiline_comment(char* string){
  if(strlen(string) < 2){ return false; }
  return (strcmp(string, "/*") == 0) ? true : false;
}

bool is_comment(char* string){
  if(strlen(string) == 0){ return false; }
  else if(string[0] == '/'){ return true; }
  return is_multiline_comment(string) || false;
}

bool in_str(char* string, const char* pattern){
  return strstr(string, pattern) != NULL ? true : false;
}

char* strip(char* string){
  if(string == NULL){ return string; }
  while(*string != '\0' && isspace(*string) && !isalpha(*string)){*string++;}
  return string;
}

char* remove_non_alpha(char* string){
  char* s = (char*)malloc(sizeof(char)*strlen(string));
  char c;
  bool in_quotes = false;
  for(size_t i = 0; i < strlen(string); ++i){
    c = string[i];
    if(isalpha(c) && !in_quotes){ strncat(s, &c, 1); }
    else if(c == '\"'){ in_quotes = true; }
    else if(c == '\"' && (in_quotes)){ in_quotes = false; }
    else if(isspace(c)){ strncat(s, " ", 1); }
    else if(c == '_'){ strncat(s, "_", 1); }
    else{ strncat(s," ", 1); }
  }
  return s;
}

void misc_tests(){
  char* message = "   This is before";
  if(is_multiline_comment("/*")){
    printf("is multiline!\n");
  }
  if(in_str(message, "is")){
    printf("is <- present in message\n");
  }
  char* a = "(Hello;.<::?> World)";
  printf("%s\n", remove_non_alpha(a));
}

void vars(const char* path, int number){
  printf("calling %s\n", __func__);
  struct file_* f_a = file_constructor(path, false);
  print_contents(stdout, f_a);
  tree* t = tree_create();
  char *lc, *string, *token, *mutate;
  bool in_comment = false;
  for(int i = 0; i < f_a->length; ++i){
    lc = f_a->contents[i];
    if(is_comment(lc)){
      if(is_multiline_comment(lc) && !in_str(lc, "*/")){
        in_comment = true;
      }
    }
    else if((strlen(lc) > 1) && isalpha(lc[0]) && !in_comment || isspace(lc[0])){
      string = remove_non_alpha(lc);
      string = strip(string);
      token = strtok(string, " ");
      while(token != NULL){
        tree_add(t, token, number, i);
        token = strtok(NULL, " ");
      }
    }
    if(in_str(lc, "*/")){
      in_comment = false;
    }
  }
  tree_print(t);
  tree_clear(t);
  free(t);
  file_destructor(f_a);
}

int main(int argc, const char* argv[]){
  if(argc < 2){
    fprintf(stderr, "Usage: %s <file> <n-characters>\n", *argv);
    return -1;
  }
  ++argv;
  const char* path = *argv++;
  int n = atoi(*argv++);
  vars(path, n);
  return 0;
}

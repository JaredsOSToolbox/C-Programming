#include "split.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void test_strtok_(char* string, char delimiter, size_t size_){
  char** output = split(string, delimiter);
  size_t element_count_ = size_of_string_array(output);
  print_split_string(output);
  assert(element_count_ == size_);
  free(output);
  printf("\n");
}

void all_strtok_tests_(){
  test_strtok_("Hello World", ' ', 2);
  test_strtok_("Hello|World", '|', 2);
  test_strtok_("Hello,World,Moon", ',', 3);
  test_strtok_("Hello,World|Moon", ',', 2);
}

char* strtok_j(char *string, const char *delimiter){
  static char *token;
  static char *next;
  char *m;
  // if we have nothing as our delimiter, don't cut the string
  if(delimiter == NULL){ return NULL; }
  // if the string is not null, then the next char* is what we wanr
  token = (string) ? string : next;
  if(token == NULL){ return NULL; }
  m = strstr(token, delimiter);
  if(m){
    next = m + strlen(delimiter);
    *m = '\0';
  } else{
    next = NULL;
  }
  return token;
}

int main(int argc, const char* argv[]){
  /*all_strtok_tests_();*/
  /*char h[BUFSIZ];*/
  /*strcpy(h, "Hello,|World,|");*/
  /*printf("%s\n", strtokm(h, ",|"));*/

  char *token[80];
  int i = 0;
  char content[BUFSIZ] = "Hello,Jared,Dyreson";
  char delimiter[BUFSIZ] = ",";
  token[i] = strtokm(content, delimiter);
  while(token[i] != NULL){
    i++;
    token[i] = strtokm(NULL, delimiter);
  }
  for(int j = 0; j <= (i-1); j++){
    printf("%s\n", token[j]);
  }
  printf("content of content: %s\n", content);
  return 0;
}

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 10000

// TODO
// read file
// read stdin

struct line_t{
  char* line[MAX_LINE_LEN];
  size_t line_n;
};

void set_line(struct line_t* object, size_t s){
  object->line_n = s;
}

void set_line_content(struct line_t* object, char* line){
  fprintf(stdout, "recieving %s\n", line);
  strncpy(object->line, line, strlen(line));
}

struct line_t* constructor_(char* line, size_t ln){
  struct line_t *l = (struct line_t*)malloc(sizeof(struct line_t));
  set_line(l, ln);
  set_line_content(l, line);
  return l;

}
void destructor_(struct line_t* object){
  if(object != NULL){ 
      free(object); 
  }
}

void read_file_(FILE* input){
  char c;
  /*char* line = (char*)malloc(MAX_LINE_LEN+1*sizeof(char));*/
  struct line_t arr[10];
  /*struct */
  int lc = 0;
  int l_index = 0;
  int buffer_index = 0;
  while((c = fgetc(input)) != EOF){
    if(c == '\n'){ 
      ++lc; 
      
    }
    else{
      /*line[index++] = c; */
    }
  }
  fprintf(stdout, "line count is: %d\n", lc);
}

int main(int argc, const char* argv[]){
  /*struct line_t* l = constructor_("Hello World", 1);*/
  /*fprintf(stdout, "Content of l: %s\n", l->line);*/
  /*destructor_(l);*/

  FILE* input = fopen("../../README.md", "r");
  read_file_(input);
  fclose(input);


  /*regex_t regex;*/
  /*int reti;*/
  /*const char* line = "Hello World";*/
  /*char line[100] = "Hello World";*/
  /*const char* pattern = "orld";*/
  /*regmatch_t rm[2];*/

  /*reti = regcomp(&regex, "^a[[:alnum:]]", 0);*/
  /*if(reti){*/
    /*fprintf(stderr, "Could not compile regular expression!\n");*/
    /*exit(1);*/
  /*}*/
  /*reti = regexec(&regex, "abc\ndef", 0, rm, 0);*/
  /*if(!reti){ fprintf(stdout, "Match starting at %d and ending at %d!\n", rm[0].rm_so, rm[0].rm_eo); }*/
  /*regfree(&regex);*/
  /*return 0;*/
}

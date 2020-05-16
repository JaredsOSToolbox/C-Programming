#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/file_struct.h"

#define NUMBER_OF_STRINGS 100
#define MAX_STRING_SIZE 200
#define PADDING_SIZE 76

struct file_* file_constructor(const char* file_path){
  struct file_ *f =  (struct file_*)malloc(sizeof(struct file_));
  f->length = 0;
  f->contents = malloc(NUMBER_OF_STRINGS * sizeof(char*));
  f->file_path = malloc(sizeof(char*));
  sprintf(f->file_path, "%s", file_path);
  for (int i = 0; i < NUMBER_OF_STRINGS; i++){
      f->contents[i] = malloc((MAX_STRING_SIZE+1) * sizeof(char));
  }
  read_contents(f);
  return f;
}

void file_destructor(struct file_* f){
  for(int i = 0; i < NUMBER_OF_STRINGS; ++i){
    free(f->contents[i]);
  }
  free(f->contents);
  free(f->file_path);
  free(f);
}

bool is_eq(struct file_* a, struct file_* b){
  bool fn = (strcmp(a->file_path, b->file_path) == 0);  
  bool len = (a->length == b->length);
  bool contents = compare_contents(a, b);
  return (fn && len && contents);
}

bool is_neq(struct file_*a, struct file_* b){ return !is_eq(a, b); }

void repr(struct file_* f){
  printf("Path: %s\n", f->file_path);
  printf("File length: %d\n", f->length);
  printf("Contents of file: \n");
  print_contents(stdout, f);
}


// member functions

void read_contents(struct file_* f){
  char *line;
  size_t len = 0;
  ssize_t read;
  int line_number_ = 0;

  FILE* file_in = fopen(f->file_path, "r");

  if(file_in == NULL){
    fprintf(stderr, "Could not open file, cowardly refusing!\n");
    file_destructor(f);
    exit(1);
  }

  while ((read = getline(&line, &len, file_in)) != EOF) {
    char* pos;
    if((pos = strchr(line, '\n')) != NULL){ *pos = '\0'; }
    sprintf(f->contents[line_number_], "%s", line);
    line_number_++;
  }
  f->length = line_number_;
}

void print_contents(FILE* stream, struct file_* f){
  for(int i = 0; i < f->length; ++i){
    fprintf(stream, "[%d]: %s\n", i, f->contents[i]);
  }
}

void print_contents_side_by_side(FILE* stream, struct file_* a, struct file_* b){
  int longest_side_ = (a->length < b->length) ? b->length : a->length;
  int shortest_side_ = (a->length < b->length) ? a->length : b->length;
  char padding[PADDING_SIZE];
  memset(padding, ' ', PADDING_SIZE-1);
  padding[PADDING_SIZE-1] = '\0';
  for(int i = 0; i < longest_side_; ++i){
    char leftside[BUFSIZ], rightside[BUFSIZ], nonvoid_line[BUFSIZ];
    sprintf(nonvoid_line, "%-75s", (i < shortest_side_) ? a->contents[i] : "");
    sprintf(leftside, "%s", (i < shortest_side_) ? nonvoid_line : padding);
    sprintf(rightside, "%s\n", b->contents[i]);
    fprintf(stream, "%s %s", leftside, rightside);
  }
}

void print_contents_side_by_side_mod(FILE* stream, struct file_* a, struct file_* b){
  int longest_side_ = (a->length < b->length) ? b->length : a->length;
  int shortest_side_ = (a->length < b->length) ? a->length : b->length;
  int begin_shortest_index = 5,  j = 0;
  printf("%d\n", begin_shortest_index);
  char padding[PADDING_SIZE];
  memset(padding, ' ', PADDING_SIZE-1);
  padding[PADDING_SIZE-1] = '\0';
  for(int i = 0; i < longest_side_+begin_shortest_index; ++i){
    char leftside[BUFSIZ], rightside[BUFSIZ], nonvoid_line[BUFSIZ];
    sprintf(nonvoid_line, "%-75s", (i > begin_shortest_index) ? a->contents[j++] : padding);

    sprintf(leftside, "%s", nonvoid_line);
    sprintf(rightside, "%s\n", b->contents[i]);
    fprintf(stream, "%s %s", leftside, rightside);
  }
}


bool compare_contents(struct file_* a, struct file_* b){
  if(a->length != b->length){ return false; }
  for(int i = 0; i < a->length; ++i){
    if(strcmp(a->contents[i], b->contents[i]) != 0){ return false; }
  }
  return true;
}

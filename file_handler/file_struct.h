#pragma once
#include <stdbool.h>
struct file_{
  char** contents;
  char* file_path;
  int length;
};

bool compare_contents(struct file_* a, struct file_* b);
bool is_eq(struct file_* a, struct file_* b);
struct file_* file_constructor(const char* file_path);
void file_destructor(struct file_* f);
void print_contents(FILE* stream, struct file_* f);
void print_contents_side_by_side(FILE* stream, struct file_* a, struct file_* b);
void read_contents(struct file_* f);
void repr(struct file_* f);


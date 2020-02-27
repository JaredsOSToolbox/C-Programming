#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int array[10] = {1, 2, 3, 4, 15, 6, 7, 8, 9, 10};
int small[1] = {1};
const char string[] = "Hello";

struct node{
  int data_;
  struct node* next_;
};

int sum(int* p, size_t n){
  if(n == 1){ return *p; }
  return *p + sum(p+1, n-1);
}

int max_helper(int a, int b){ return a > b ? a : b; }

int max_(int *p, size_t n){
  if(n == 1){ return *p; }
  return max_helper(*p, max_(p+1, n-1));
}


// linked list example

int llsum(struct node* p){
  if(p->next_ == NULL){ return p->data_; }
  return p->data_ + llsum(p->next_);
}
void reverse(char str[]){
  for(int i = strlen(string); i >= 0; --i){
    fputc((char)str[i], stdout);
  }
  fputc('\n', stdout);
}
void print_reverse(const char* s){
  if(*s == '\0'){ return; }
  print_reverse(s+1);
  fputc(*s, stdout);
}

int non_recursive_sum(int* container, size_t n){
  int counter = 0;
  while(n-- > 0){ counter+=(*container++); }
  return counter;
}

size_t strlen_(const char* s){
  size_t counter = 0;
  while(*s++ != '\0'){
    counter++;
  }
  return counter;
}

char* strcpy_(char* destination, const char* source){
  // page 249
  // reimplement string.h lol
  char* p = destination;
  while((*destination++ = *source++) != '\0'){}
  return p;
}

char* strncpy_(char* destination, const char* source, size_t n){
  char* p = destination;
  while((*destination++ = *source++) != '\0' && n-- > 0){}
  *destination = '\0';
  return p;
}
int main(int argc, const char* argv[]){
  /*int s = max_(array, 10);*/
  /*const char array[] = "Hello World";*/
  /*print_reverse(array);*/
  /*int s = non_recursive_sum(array, 10);*/
  /*int s = sum(array, 10);*/
  const char* message = "Hello";
  fprintf(stdout, "length of message (%s) is: %zu\n", message, strlen_(message));
  char example[10];
  strncpy_(example, message, 3);
  fprintf(stdout, "%s\n", example);
  /*fprintf(stdout, "%d\n", s);*/
  return 0;
}

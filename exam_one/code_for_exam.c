#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Written by Jared Dyreson
// All rights reserved

void count(){
  printf("Enter lines of text here: ....\n");
  int c = 0, nl = 0, nc = 0, nt = 0, nbackslash = 0;
  while((c = fgetc(stdin)) != EOF){
    if(c == '\n'){ ++nl; }
    else if(c == '\t'){ ++nt; }
    else if(c == '\\'){ ++nbackslash; }
    else if(isalpha(c)){ ++nc; }
  }
  printf("lines: %d\n", nl);
  printf("tabs: %d\n", nt);
  printf("backslashes: %d\n", nbackslash);
  printf("alphanumeric: %d\n", nc);
}

// Identify the SL functions that do the following
// (2) Find the first character c in a const char* s ------> strchr (<string.h>)
// (3) Find the length of the prefix of const char* s that has characters in const char* t --------> 
// (4) Terminates a program immediately ------> exit (<stdlib.h>)
// (5) Open the file "midterm.txt" in read mode ---> fopen



// BEGIN STRING.H IMPLEMENTATION
char* strcpy_(char* s, const char* t){
  char* p = s;
  while((*t != '\0') && (*s++ = *t++)){}
  return p;
}

void test_strcpy_(){
  char hello[strlen("Hello")];
  memset(hello, 0, sizeof(char));
  printf("%s\n", strcpy_(hello, "Hello"));
}

char* strncat_(char* s, const char* t, size_t n){
  char* ptr = s + strlen(s);
  while((*ptr++ = *t++) && (*s != '\0') && (--n > 0)){}
  *ptr = '\0';
  return s;
}

void test_strncat_(){
  char destination[30];
  strcpy(destination, "Hello");
  char source[] = "World";
  printf("contents of t: %s\n", strncat_(destination, source, 5));
}

int strcmp_(const char* s, const char* t){
  while(*s++ == *t++ && (*s != '\0')){}
  return *s - *t;
}

void test_strcmp(){
  const char a[] = "Hello";
  const char b[] = "Hello";
  int value = strcmp_(a, b);
  printf("value of value: %d\n", value);
  if(value == 0){
    printf("they are the same!\n");
  }
  else if(value > 1){
    printf("a is bigger than b\n");
  }
  else{
    printf("b is bigger than a\n");
  }
}

// END STRING.H IMPLEMENTATION




// BEGIN SQUARE ADT IMPLEMENTATION

typedef struct point point;
struct point{ double x, y; };

typedef struct square square;
struct square{ point ul; size_t side; };

square* square_constructor(double ulx, double uly, double side){
  square* s = (square *)malloc(sizeof(square));
  s->ul.x = ulx;
  s->ul.y = uly;
  s->side = side;
  return s;
}

void square_destructor(square* s){ free(s); }

void square_move(square* sq, double x, double y){
  // updates position
  sq->ul.x = x;
  sq->ul.y = y;
}

void square_expandby(square* sq, double lambda){
  // scale the square by a constant lambda
  sq->ul.x*=lambda;
  sq->ul.y*=lambda;
  sq->side*=lambda;
}

double square_area(square* sq){ return sq->side * sq->side; }
double square_perimeter(square* sq){ return 4 * sq->side; }

void square_repr(square* sq){
  printf("Coordinate: (%g, %g)\nSide length: %zu\nArea: %g\nPerimeter: %g\n",
            sq->ul.x, sq->ul.y, sq->side, square_area(sq), square_perimeter(sq));
}

void test_square(double ulx, double uly, double side){
  printf("Constructing sqaure...\n");
  printf("==========================\n");
  square* s = square_constructor(ulx, uly, side);
  square_repr(s);
  printf("==========================\n");
  printf("Updating coordinate to (2, 2)\n");
  printf("==========================\n");
  square_move(s, 2, 2);
  square_repr(s);
  printf("===============================\n");
  printf("Expanding squre by lambda = 10\n");
  printf("===============================\n");
  square_expandby(s, 10);
  square_repr(s);
  printf("==========================\n");
  square_destructor(s);
  printf("\n\n");
}

void square_tests(){
  test_square(0, 0, 10);
  test_square(1, 1, 5);
}

// END SQUARE ADT IMPLEMENTATION

int main(){
  square_tests();
  return 0;
}

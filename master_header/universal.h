#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define IN true
#define OUT false

bool istab(char c){ return (c == '\t'); }
bool isnl(char c){ return (c == '\n'); }


void cat(FILE* in, FILE* out){
  char c;
  while((c = fgetc(in)) != EOF){
    if(istab(c)){ fprintf(out, "^I"); }
    else if(isnl(c)){ fprintf(out, "$\n"); }
    else{ fputc(c, out); }
  }
}

void wc_(FILE* in, FILE* out){
  char c;
  int cc, lc, wc;
  bool state = IN;
  cc = 0;

  while((c = fgetc(in)) != EOF){
    if(isspace(c)){
      state = OUT;
      ++wc;
    }
    if(isnl(c)){
      state = OUT;
      ++lc;
    }
    ++cc;
  }

  fprintf(out, "Char count: %d\nLine count: %d\nWord count: %d\n", cc, lc, wc);
}

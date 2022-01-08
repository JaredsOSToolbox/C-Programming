#include <stdio.h>

unsigned setbits_(unsigned x, int p, int n, unsigned y){
  unsigned a = x & ~(~(~0U << n) << (p+1-n));
  unsigned b = (y & ~(0U << n)) << (p+1-n);
  return (a | b);
}

unsigned getbits(unsigned x, int p, int n){
  return (x >> (p+1-n)) & ~(~0 << n);
}


int main(int argc, const char* argv[]){
  /*fprintf(stdout, "%u\n", setbits_(5732, 6, 3, 9823));*/
  fprintf(stdout, "%u\n", getbits(0xf994, 6, 3));
  return 0;
}

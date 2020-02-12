#include <stdio.h>
#include <string.h>

#define ARR_LEN 3

void c_swap(char* x, char* y){
  char t = *x;
  *x = *y;
  *y = t;
}

void swap(int* x, int* y){
  int t = *x;
  *x = *y;
  *y = t;
}

void rev_array(int array[], int s, int e){
  int t;
  if(s >= e){ return; }
  t = array[s];
  array[s] = array[e];
  array[e] = t;
  rev_array(array, s+1, e-1);
}

void new_rev(char* array){
  char* p = array;
  size_t len = strlen(array);
  char* t = &array[len-1];
  for(int i = 0; i < (len/2); ++i){
    swap()
  }
}

int main(int argc, const char* argv[]){
  int index = 0;
  int arr[3] = {1, 2, 3};
  rev_array(arr, 0, 2);

  for(int i = 0; i < ARR_LEN; ++i){
    fprintf(stdout, "%d -----> %d\n",i, arr[i]);
  }
  /*swap(&arr[0], &arr[1]);*/
  /*fprintf(stdout, "0: %d\t1: %d\n", arr[0], arr[1]);*/
  /*return 0;*/
}

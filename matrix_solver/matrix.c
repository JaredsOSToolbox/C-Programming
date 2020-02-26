#include <stdio.h>
#include <stdbool.h>
#include "matrix_header.h"

int main(int argc, const char* argv[]){
  int matrix[M][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int matrix_b[M][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  FILE* output_a = fopen("matrix_a", "w");
  FILE* output_b = fopen("matrix_b", "w");

  int* transposed = transpose(matrix);
  print_matrix_(output_a, transposed, M, N);
  print_matrix_(output_b, matrix, M, N);

  int* new_m = matrix_multiplication(matrix, matrix_b);
  print_matrix_(stdout, new_m, M, N);
  free(new_m);

  free(transposed);
  fclose(output_a);
  fclose(output_b);


  return 0;
}

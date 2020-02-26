#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

// these are the dimensions of the matrix
#define M 3
#define N 3

//struct matrix_t{
  //int a, b;
  //int content[a][b];
//};

void swap(int* a, int* b){
  int t = *a;
  *a = *b;
  *b = t;
}

void print_matrix_(FILE* output, int matrix[M][N], 
                    int m, int n){
  // print the content of the matrix in order

  int counter = 0;
  for(int x = 0; x < m; ++x){
    for(int y = 0; y < n; ++y){
      ++counter;
      fprintf(output, "%d", matrix[x][y]);
      if(counter % M == 0){ fprintf(output, "\n"); }
      else{ fprintf(output, "\t"); }
    }
  }
}

int* get_column(int matrix[M][N], int column_number){
  int* pointer = (int*)malloc(N+1*sizeof(int));
  int counter = 0;
  for(int y = 0; y < N; ++y){
    pointer[counter++] = matrix[y][column_number];
  }
  return pointer;
}

int* get_row(int matrix[M][N], int row_number){
  int* pointer = (int*)malloc(M+1*sizeof(int));
  int counter = 0;
  for(int x = 0; x < M; ++x){
    pointer[counter++] = matrix[row_number][x];
  }
  return pointer;
}

int* get_diagonal(int matrix[M][N]){
  int* pointer = (int*)malloc(M+1*sizeof(int));
  int counter = 0;
  for(int x = 0; x < M; ++x){
    for(int y = 0; y < N; ++y){
      if(x == y){ pointer[counter++] = matrix[x][y]; }
    }
  }
  return pointer;
}

int* transpose(int matrix[M][N]){
  int* transposed_matrix = (int *)malloc(M * N * sizeof(int));
  for(int x = 0; x < M; ++x){
    for(int y = 0; y < N; ++y){
      *(transposed_matrix+y*N+x) = matrix[x][y];
    }
  }
  return transposed_matrix;
}

int sum(int row[], int column[], int size, char operator){
  int counter = 0;
  for(int i = 0; i < size; ++i){ 
    switch(operator){
      case '+':
        counter+=(row[i]+column[i]);
        break;
      case '-':
        counter+=(row[i]-column[i]);
        break;
    }
  }
  return counter;
}

int* matrix_multiplication(int matrix_a[M][N], int matrix_b[M][N]){
  int* new_matrix = (int *)malloc(M * N * sizeof(int));
  for(int x = 0; x < M; ++x){
    for(int y = 0; y < N; ++y){

      int* column_a = get_column(matrix_a, x);
      int* row_a = get_row(matrix_a, y);

      int* column_b = get_column(matrix_b, x);
      int* row_b = get_row(matrix_b, y);

      int counter = 0;
      for(int i = 0; i < M; ++i){
        counter+=(column_a[i]*row_a[i]);
      }
      *(new_matrix+x*N+y) = counter;
      counter = 0;
      free(column_a);
      free(column_b);
      free(row_a);
      free(row_b);
    }
  }
  return new_matrix;
}

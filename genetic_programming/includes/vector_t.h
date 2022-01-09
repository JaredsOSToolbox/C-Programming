#pragma once
#include <stdio.h>

struct vector_t {
    int* data;
    int size;
    int position;
    int associate_number;
};

struct vector_t* vector_t_constructor(int base_ten);

void vector_t_destructor(struct vector_t* vec);
void vector_t_print(FILE* fd, struct vector_t* vec);
void vector_t_update_array(struct vector_t* vec, int number);

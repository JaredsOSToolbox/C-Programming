#pragma once

#define CROSSOVER_SPAN 4
#define PARENT_SPAN 9

struct tuple_t {
    unsigned long long int x;
    unsigned long long int y;
};

struct tuple_t* tuple_t_constructor(int x, int y);

void tuple_t_destructor(struct tuple_t* t);

void tuple_t_print(struct tuple_t* t);

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct rect_t {
    int X, Y, Width, Height;
} rect_t;

typedef struct pice_t {
    int X, Y;
    int Width, Height;
    bool Set;
} pice_t;

int intersect(rect_t pos, pice_t pice);
void print(pice_t *array);
void print_pos(rect_t *free_pos, int count);
void rotate(pice_t *pice);
bool is_square(pice_t pice);
void sort();
void copy_to_array(pice_t *copy_to, pice_t *copy_from);
void copy_to_pos(rect_t *copy_to, rect_t* copy_from);
bool out_of_bounds(rect_t free_pos, pice_t pice);
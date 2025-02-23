#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define true 1
#define false 0

// Constants
const int g_next_right = 1;
const int g_next_down = 2;

// Structs
typedef struct rect_t {
    int X, Y, Width, Height;
} rect_t;

typedef struct pice_t {
    int X, Y;
    int Width, Height;
    bool Set;
    int Next;

} pice_t;

typedef struct cut_t
{
    int X, Y;
    int Width, Height;
} cut_t;

typedef struct cut_array_t {
    cut_t *cuts;
    int num_of_cuts;
} cut_array_t;

// Declarations
int intersect(rect_t pos, pice_t pice, pice_t *array);
int get_area(pice_t pice);
void print(pice_t *array);
void print_pos(rect_t *free_pos, int count);
void rotate(pice_t *pice);
bool is_square(pice_t pice);
void sort();
void copy_to_array(pice_t *copy_to, pice_t *copy_from);
void copy_to_pos(rect_t *copy_to, rect_t* copy_from);
void copy_to_cut(cut_array_t *copy_to, cut_array_t *copy_from);
bool out_of_bounds(rect_t free_pos, pice_t pice);
int get_full_area(pice_t *pices_array, int count);
void sort_array(pice_t *array, int count);
int max_area(pice_t *pices_array);
bool intersect_with_cut(cut_array_t *array, pice_t pice);
int make_cut(cut_array_t *cut_array, pice_t *pices_array, pice_t *pice, rect_t *pos);
void free_cuts(cut_array_t *cut_array);
bool is_pices_equa(pice_t pice1, pice_t pice2);
void print_cuts(cut_array_t *cuts);
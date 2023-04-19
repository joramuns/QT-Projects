#ifndef PARS_H
#define PARS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pars_counters {
    int count_vertex;
    int count_side;
    int size_sort_array;
    int size_unsort_memory;
    int size_sort_memory;
} pars_counters;

float *array_sort(char *filename, pars_counters *View);
float my_atof(char *str);
int my_atoi(const char *str);

#endif // PARS_H
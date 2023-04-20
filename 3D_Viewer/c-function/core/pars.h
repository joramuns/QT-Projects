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

float *array_sort(FILE *obj, pars_counters *View);
void unsort_array_fill(char *line, pars_counters *View, float **point_array);
void sort_array_fill(char *line, pars_counters *View, float **sorted_array,
                     float *point_array);
float my_atof(char *str);
int my_atoi(const char *str);

#endif // PARS_H

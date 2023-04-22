#ifndef PARS_H
#define PARS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pars_counters {
  int count_vertex;
  int count_side;
  int size_sort_array;
  int size_unsort_memory;
  int size_sort_memory;
  float *sorted_array;
} Pars_counters;

void *array_sort(FILE *obj, Pars_counters *view);
void unsort_array_fill(char *line, Pars_counters *view, float **point_array);
void sort_array_fill(char *line, Pars_counters *view, float *point_array);
float my_atof(char *str);
int my_atoi(const char *str);

#endif // PARS_H

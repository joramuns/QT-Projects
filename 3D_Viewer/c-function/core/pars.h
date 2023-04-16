#ifndef PARS_H
#define PARS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float *array_sort(float *sorted_array, char *filename, int *count_vertex,
                  int *count_side, int *size_sort_array);
float my_atof(char *str);
int my_atoi(const char *str);
void memory_alloc(float *array, int *size);

#endif // PARS_H
#ifndef PARS_H
#define PARS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float *array_sort(float *sorted_array, char *filename, int *count_vertex, int *count_side);
float my_atof(char *str);
int my_atoi(const char *str);

#endif // PARS_H
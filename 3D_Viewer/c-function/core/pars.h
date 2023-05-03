#ifndef PARS_H
#define PARS_H

#include "core.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_EPS 1e-6

/*!
  \brief Структура, которая хранит в себе все полезные счетчики и массив точек
  после парчинга
*/

typedef struct Pars_counters {
  int count_vertex;
  int count_side;
  int size_sort_array;
  int size_unsort_memory;
  int size_sort_memory;
  float *sorted_array;
} Pars_counters;

void array_sort(FILE *obj, Pars_counters *view);
void unsort_array_fill(char *line, Pars_counters *view, float **point_array);
void sort_array_fill(char *line, Pars_counters *view, float *point_array);
float my_atof(char *str);
int my_atoi(const char *str);
int f_counter(char *line);
void polygone_fill(Pars_counters *view, float *point_array, int vertex_number);
void memory_of_sort_alloc(Pars_counters *view);
void normalize(Pars_counters *view);
float maxpoint(Pars_counters *view);
void point_assignment(Pars_counters *view, float *point_array,
                      int index_of_point);
#endif // PARS_H

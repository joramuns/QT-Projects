/*!
\file
\brief Заголовочный файл с описанием структуры и функций используемых для при
парсинге obj файла
*/
#ifndef PARS_H
#define PARS_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"

/*!
  \brief Макрос используется для сравнения чисел с плавающей точкой.
*/
#define S21_EPS 1e-6

/// Структура для хранения массива координат
/*!
  \brief Структура, которая хранит в себе все полезные счетчики и массив
  координат точек после отработки парсера, по координатам этих точек в
  последствии проводится отрисовка модели
*/
typedef struct Pars_counters {
  int count_vertex;  ///< счетчик вершин
  int count_edges;   ///< счетчик сторон
  int size_sort_array;  ///< размер массива после сортировки
  int size_unsort_memory;  ///< размер массива до сортировки
  int size_sort_memory;  ///< размер выделенной памяти после сортировки
  float
      *sorted_array;  ///< указатель на массив координат точек в верном порядке
} Pars_counters;

void array_sort(FILE *obj, Pars_counters *view);
void unsort_array_fill(char *line, Pars_counters *view, float **point_array);
void sort_array_fill(char *line, Pars_counters *view, float *point_array);
float my_atof(char *str);
int my_atoi(const char *str);
void memory_of_sort_alloc(Pars_counters *view);
void normalize(Pars_counters *view);
float maxpoint(Pars_counters *view);
void point_assignment(Pars_counters *view, float *point_array,
                      int index_of_point);
#endif  // PARS_H

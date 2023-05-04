/*!
\file
\brief Заголовочный файл с описанием функций аффинных преобразований модели
*/
#ifndef CORE_H
#define CORE_H

#include "../support/support_function.h"
#include <stdio.h>

void coordinate_change(float x, float y, float z, float *point_array,
                       int size_sort_array);
void turn_matrix_x(float theta, float *point_array, int size_sort_array);
void turn_matrix_y(float theta, float *point_array, int size_sort_array);
void turn_matrix_z(float theta, float *point_array, int size_sort_array);
void scaling(float coef, float *point_array, int size_sort_array);

#endif // CORE_H

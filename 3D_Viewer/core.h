#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdio.h>

float *sort_array(float *point_array);
void coordinate_change(float x, float y, float z, float *point_array);
void identity_matrix(float *matrix_scale);
void move_matrix(float *matrix_scale, float *coordinates);

#endif // CORE_H
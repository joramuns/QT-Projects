#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float *sort_array(float *point_array);
void coordinate_change(float x, float y, float z, float *point_array);
void identity_matrix(float *matrix_scale);
void create_move_matrix(float *matrix_scale, float *coordinates);
void create_turn_matrix_x(float *matrix_turn, float theta);
void turn_matrix_x(float theta, float *point_array);
void create_turn_matrix_y(float *matrix_turn, float theta);
void turn_matrix_y(float theta, float *point_array);
void create_turn_matrix_z(float *matrix_turn, float theta);
void turn_matrix_z(float theta, float *point_array);
void scaling (float coef, float *point_array);
void cerate_scale_matrix(float *matrix_scale, float coef);
void matrix_mul(float *matrix_scale, float *point_array);

#endif // CORE_H
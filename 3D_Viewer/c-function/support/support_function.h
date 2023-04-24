#ifndef SUPPROT_FUNCTION
#define SUPPROT_FUNCTION

#include <stdlib.h>
#include <math.h>

float *sort_array(float *point_array);
void identity_matrix(float *matrix_scale);
void create_move_matrix(float *matrix_scale, float *coordinates);
void create_turn_matrix_x(float *matrix_turn, float theta);
void create_turn_matrix_y(float *matrix_turn, float theta);
void create_turn_matrix_z(float *matrix_turn, float theta);
void create_scale_matrix(float *matrix_scale, float coef);
void matrix_mul(float *matrix_scale, float *point_array, int size_ar);
float my_atof(char *str);
int my_atoi(const char *str);

#endif //  SUPPROT_FUNCTION

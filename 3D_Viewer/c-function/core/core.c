#include "core.h"


void coordinate_change(float x, float y, float z, float *point_array, int size_sort_array) {
  float matrix_scale[4][4] = {0};
  identity_matrix(matrix_scale[0]);
  float coordinates[3] = {x, y, z};
  create_move_matrix(matrix_scale[0], coordinates);
  matrix_mul(matrix_scale[0], point_array, size_sort_array);
}

void turn_matrix_x(float theta, float *point_array, int size_sort_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_x(matrix_turn[0], theta);
  matrix_mul(matrix_turn[0], point_array, size_sort_array);
}

void turn_matrix_y(float theta, float *point_array, int size_sort_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_y(matrix_turn[0], theta);
  matrix_mul(matrix_turn[0], point_array, size_sort_array);
}

void turn_matrix_z(float theta, float *point_array, int size_sort_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_z(matrix_turn[0], theta);
  matrix_mul(matrix_turn[0], point_array, size_sort_array);
}

void scaling(float coef, float *point_array, int size_sort_array) {
  float matrix_scale[4][4] = {0};
  identity_matrix(matrix_scale[0]);
  create_scale_matrix(matrix_scale[0], coef);
  matrix_mul(matrix_scale[0], point_array, size_sort_array);
}

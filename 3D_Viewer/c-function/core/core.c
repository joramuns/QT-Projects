#include "core.h"


void coordinate_change(float x, float y, float z, float *point_array) {
  float matrix_scale[4][4] = {0};
  identity_matrix(matrix_scale[0]);
  float coordinates[3] = {x, y, z};
  create_move_matrix(matrix_scale[0], coordinates);
  matrix_mul(matrix_scale, point_array);
}

void turn_matrix_x(float theta, float *point_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_x(matrix_turn, theta);
  matrix_mul(matrix_turn, point_array);
}

void turn_matrix_y(float theta, float *point_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_y(matrix_turn, theta);
  matrix_mul(matrix_turn, point_array);
}

void turn_matrix_z(float theta, float *point_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_z(matrix_turn, theta);
  matrix_mul(matrix_turn, point_array);
}

void scaling(float coef, float *point_array) {
  float matrix_scale[4][4] = {0};
  identity_matrix(matrix_scale[0]);
  cerate_scale_matrix(matrix_scale, coef);
  matrix_mul(matrix_scale, point_array);
}

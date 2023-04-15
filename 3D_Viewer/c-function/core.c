#include "core.h"

float *sort_array(float *point_array) {
  float kek_point[] = {-0.5, -0.5, -0.5, 1,   -0.5, 0.5,
                       -0.5, 1,    0.5,  0.5, -0.5, 1};
  point_array = (float *)malloc(12 * sizeof(float));
  for (int i = 0; i < 12; i++) {
    point_array[i] = kek_point[i];
  }
  return point_array;
}

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

void identity_matrix(float *matrix_scale) {
  for (int i = 0; i < 4; i++)
    matrix_scale[i + i * 4] = 1.0;
}

void create_move_matrix(float *matrix_scale, float *coordinates) {
  for (int i = 0; i < 3; i++) {
    matrix_scale[3 + i * 4] = coordinates[i];
  }
}

void create_turn_matrix_x(float *matrix_turn, float theta) {
  matrix_turn[5] = cos(theta);
  matrix_turn[6] = -sin(theta);
  matrix_turn[9] = sin(theta);
  matrix_turn[10] = cos(theta);
}

void create_turn_matrix_y(float *matrix_turn, float theta) {
  matrix_turn[0] = cos(theta);
  matrix_turn[2] = sin(theta);
  matrix_turn[8] = -sin(theta);
  matrix_turn[10] = cos(theta);
}

void create_turn_matrix_z(float *matrix_turn, float theta) {
  matrix_turn[0] = cos(theta);
  matrix_turn[1] = -sin(theta);
  matrix_turn[4] = sin(theta);
  matrix_turn[5] = cos(theta);
}

void cerate_scale_matrix(float *matrix_scale, float coef) {
  for (int i = 0; i < 3; i++)
    matrix_scale[i + 4 * i] = coef;
}

void matrix_mul(float *matrix_scale, float *point_array) {
  int size_ar = 12;
  for (int k = 0; k < size_ar / 4; k++) {
    float result[4] = {0};
    for (int i = 0; i < 4; i++) {
      float sum = 0;
      for (int j = 0; j < 4; j++) {
        sum += matrix_scale[i * 4 + j] * point_array[j + k * 4];
      }
      result[i] = sum;
    }
    for (int m = 0; m < 4; m++) {
      point_array[k * 4 + m] = result[m];
    }
  }
}
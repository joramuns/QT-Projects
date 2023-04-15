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
  move_matrix(matrix_scale[0], coordinates);
  matrix_mul(matrix_scale, point_array);
}

void identity_matrix(float *matrix_scale) {
  for (int i = 0; i < 4; i++)
    matrix_scale[i + i * 4] = 1.0;
}

void move_matrix(float *matrix_scale, float *coordinates) {
  for (int i = 0; i < 3; i++) {
    matrix_scale[3 + i * 4] = coordinates[i];
  }
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
      result[i]=sum;
    }
    for (int m = 0; m < 4; m++) {
      point_array[k * 4 + m] = result[m];
    } 
  }

}
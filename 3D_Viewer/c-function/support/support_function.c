#include "support_function.h"

/*!
      \brief На вход получает матрицу 4х4 заполненную нолями, создает из нее
   диагональную единичную матрицу.
*/
void identity_matrix(float *matrix_scale) {
  for (int i = 0; i < 4; i++) matrix_scale[i + i * 4] = 1.0;
}

/*!
      \brief Формирует матрицу перемещений.
*/
void create_move_matrix(float *matrix_scale, const float *coordinates) {
  for (int i = 0; i < 3; i++) {
    matrix_scale[3 + i * 4] = coordinates[i];
  }
}

/*!
      \brief Формирует матрицу поворота вокруг оси X.
*/
void create_turn_matrix_x(float *matrix_turn, float theta) {
  matrix_turn[5] = cos(theta);
  matrix_turn[6] = -sin(theta);
  matrix_turn[9] = sin(theta);
  matrix_turn[10] = cos(theta);
}

/*!
      \brief Формирует матрицу поворота вокруг оси Y.
*/
void create_turn_matrix_y(float *matrix_turn, float theta) {
  matrix_turn[0] = cos(theta);
  matrix_turn[2] = sin(theta);
  matrix_turn[8] = -sin(theta);
  matrix_turn[10] = cos(theta);
}

/*!
      \brief Формирует матрицу поворота вокруг оси Z.
*/
void create_turn_matrix_z(float *matrix_turn, float theta) {
  matrix_turn[0] = cos(theta);
  matrix_turn[1] = -sin(theta);
  matrix_turn[4] = sin(theta);
  matrix_turn[5] = cos(theta);
}

/*!
      \brief Формирует матрицу масштабирования.
*/
void create_scale_matrix(float *matrix_scale, float coef) {
  for (int i = 0; i < 3; i++) matrix_scale[i + 4 * i] = coef;
}

/*!
      \brief Перемножает матрицу 4х4 на массив координат точек, дробя массив на
   вектора 4х1.
*/
void matrix_mul(const float *matrix_scale, float *point_array, int size_ar) {
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

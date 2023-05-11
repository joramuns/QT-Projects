#include "core.h"
/*!
      \brief Производит изменение координат точек в соответствии с перемещением
   по заданной оси. \param[in] x - шаг перемещения по соответствующей оси.
      \param[in] y - шаг перемещения по соответствующей оси.
      \param[in] z - шаг перемещения по соответствующей оси.
      \param[out] point_array - указатель на массив координат точек.
      \param[in] size_sort_array - размер массива координат точек.
*/
void coordinate_change(float x, float y, float z, float *point_array,
                       int size_sort_array) {
  float matrix_scale[4][4] = {0};
  identity_matrix(matrix_scale[0]);
  float coordinates[3] = {x, y, z};
  create_move_matrix(matrix_scale[0], coordinates);
  matrix_mul(matrix_scale[0], point_array, size_sort_array);
}

/*!
      \brief Производит изменение координат точек в соответствии с углом
   поворота вокруг оси X. \param[in] theta - угол поворота. \param[out]
   point_array - указатель на массив координат точек. \param[in] size_sort_array
   - размер массива координат точек.
*/
void turn_matrix_x(float theta, float *point_array, int size_sort_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_x(matrix_turn[0], theta);
  matrix_mul(matrix_turn[0], point_array, size_sort_array);
}

/*!
      \brief Производит изменение координат точек в соответствии с углом
   поворота вокруг оси Y. \param[in] theta - угол поворота. \param[out]
   point_array - указатель на массив координат точек. \param[in] size_sort_array
   - размер массива координат точек.
*/
void turn_matrix_y(float theta, float *point_array, int size_sort_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_y(matrix_turn[0], theta);
  matrix_mul(matrix_turn[0], point_array, size_sort_array);
}

/*!
      \brief Производит изменение координат точек в соответствии с углом
   поворота вокруг оси Z. \param[in] theta - угол поворота. \param[out]
   point_array - указатель на массив координат точек. \param[in] size_sort_array
   - размер массива координат точек.
*/
void turn_matrix_z(float theta, float *point_array, int size_sort_array) {
  float matrix_turn[4][4] = {0};
  identity_matrix(matrix_turn[0]);
  create_turn_matrix_z(matrix_turn[0], theta);
  matrix_mul(matrix_turn[0], point_array, size_sort_array);
}

/*!
      \brief Производит изменение координат точек в соответствии коэфициентом
   масштабирования по всем осям. \param[in] coef - коэфициент масштабирования.
      \param[out] point_array - указатель на массив координат точек.
      \param[in] size_sort_array - размер массива координат точек.
*/
void scaling(float coef, float *point_array, int size_sort_array) {
  float matrix_scale[4][4] = {0};
  identity_matrix(matrix_scale[0]);
  create_scale_matrix(matrix_scale[0], coef);
  matrix_mul(matrix_scale[0], point_array, size_sort_array);
}

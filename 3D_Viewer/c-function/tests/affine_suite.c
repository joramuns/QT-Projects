#include "test_runner.h"
#include "../core/core.h"
#include <stdio.h>

#define ARR_SIZE 12
#define TEST_EPS 1e-05

static const float original_array[] = {
    -1.480759, 1.795634, 1.982020,  1.0, 
    -1.097703, -2.336702, -0.361380, 1.0,
    -4.594137, 3.352988, -1.273126, 1.0
};

static float *get_copy() {
  float *copy = calloc(ARR_SIZE, sizeof(float));
  for (int i = 0; i < ARR_SIZE; i++)
    copy[i] = original_array[i];

  return copy;
}

START_TEST(rotate_x_5) {
  float *array = get_copy();
  turn_matrix_x(-0.087266, array, ARR_SIZE);
  float expected[] = {
    -1.480759, 1.961545, 1.817978, 1.0,
    -1.097703, -2.359306, -0.156348, 1.0,
    -4.594137, 3.229269, -1.560514, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(array);
}

static TCase *rotations_tc(void) {
  TCase *tc = tcase_create("rotations");
  tcase_add_test(tc, rotate_x_5);

  return tc;
}

Suite *affine_suite() {
  Suite *s = suite_create("affine_suite");

  suite_add_tcase(s, rotations_tc());

  return s;
}

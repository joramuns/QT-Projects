#include "test_runner.h"
#include "../core/core.h"
#include <stdio.h>

#define ARR_SIZE 12
#define TEST_EPS 1e-05
#define S21_PI 3.141592

static float degreesToRadiand(float value) {
  return (value * S21_PI) / 180;
}

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
  turn_matrix_x(degreesToRadiand(-5), array, ARR_SIZE);
  float expected[] = {
    -1.480759, 1.961545, 1.817978, 1.0,
    -1.097703, -2.359306, -0.156348, 1.0,
    -4.594137, 3.229269, -1.560514, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(array);
}

START_TEST(rotate_counter_x_5) {
  float *array = get_copy();
  turn_matrix_x(degreesToRadiand(5), array, ARR_SIZE);
  float expected[] = {
    -1.480759, 1.616057, 2.130978, 1.0,
    -1.097703, -2.296314, -0.563662, 1.0,
    -4.594137, 3.451189, -0.976049, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(array);
}

START_TEST(rotate_y_5) {
  float *array = get_copy();
  turn_matrix_y(degreesToRadiand(-5), array, ARR_SIZE);
  float expected[] = {
    -1.647869, 1.795634, 1.845421, 1.0,
    -1.06203, -2.336702, -0.455676, 1.0,
    -4.465695, 3.352988, -1.668687, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(array);
}

START_TEST(rotate_counter_y_5) {
  float *array = get_copy();
  turn_matrix_y(degreesToRadiand(5), array, ARR_SIZE);
  float expected[] = {
    -1.30238, 1.795634, 2.103534, 1.0,
    -1.125022, -2.336702, -0.264334, 1.0,
    -4.687615, 3.352988, -0.867876, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(array);
}

START_TEST(rotate_z_5) {
  float *array = get_copy();
  turn_matrix_z(degreesToRadiand(-5), array, ARR_SIZE);
  float expected[] = {
    -1.318624, 1.917858, 1.98202, 1.0,
    -1.297183, -2.232139, -0.36138, 1.0,
    -4.284423, 3.740634, -1.273126, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++) {
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);
    }
  free(array);
}

START_TEST(rotate_counter_z_5) {
  float *array = get_copy();
  turn_matrix_z(degreesToRadiand(5), array, ARR_SIZE);
  float expected[] = {
    -1.631624, 1.659744, 1.98202, 1.0,
    -0.889869, -2.423481, -0.36138, 1.0,
    -4.868887, 2.939823, -1.273126, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(array);
}

START_TEST(movement_xyz_5) {
  float *array = get_copy();
  coordinate_change(5, 5, 5, array, ARR_SIZE);
  float expected[] = {
    3.519241, 6.795634, 6.98202,  1.0, 
    3.902297, 2.663298, 4.63862, 1.0,
    0.405863, 8.352988, 3.726874, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(array);
}

START_TEST(movement_counter_xyz_5) {
  float *array = get_copy();
  coordinate_change(-5, -5, -5, array, ARR_SIZE);
  float expected[] = {
    -6.480759, -3.204366, -3.01798,  1.0, 
    -6.097703, -7.336702, -5.36138, 1.0,
    -9.594137, -1.647012, -6.273126, 1.0
  };
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(array);
}

START_TEST(movement_xyz_0) {
  float *array = get_copy();
  coordinate_change(0, 0, 0, array, ARR_SIZE);
  float *expected = get_copy();
  for (int i = 0; i < ARR_SIZE; i++)
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);

  free(expected);
  free(array);
}

START_TEST(scale_positive) {
  float *array = get_copy();
  scaling(2, array, ARR_SIZE);
  float expected[] = {
    -2.961518, 3.591268, 3.964040, 1.000000,
    -2.195406, -4.673404, -0.722760, 1.000000,
    -9.188274, 6.705976, -2.546252, 1.000000
  };
  for (int i = 0; i < ARR_SIZE; i++) {
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);
  }

  free(array);
}

START_TEST(scale_negative) {
  float *array = get_copy();
  scaling(0.1, array, ARR_SIZE);
  float expected[] = {
    -0.148076, 0.179563, 0.198202, 1.000000,
    -0.109770, -0.233670, -0.036138, 1.000000,
    -0.459414, 0.335299, -0.127313, 1.000000
  };
  for (int i = 0; i < ARR_SIZE; i++) {
    ck_assert_float_eq_tol(array[i], expected[i], TEST_EPS);
  }

  free(array);
}

static TCase *rotations_tc(void) {
  TCase *tc = tcase_create("rotations");
  tcase_add_test(tc, rotate_x_5);
  tcase_add_test(tc, rotate_counter_x_5);
  tcase_add_test(tc, rotate_y_5);
  tcase_add_test(tc, rotate_counter_y_5);
  tcase_add_test(tc, rotate_z_5);
  tcase_add_test(tc, rotate_counter_z_5);

  return tc;
}

static TCase *movement_tc(void) {
  TCase *tc = tcase_create("movement");
  tcase_add_test(tc, movement_xyz_5);
  tcase_add_test(tc, movement_counter_xyz_5);
  tcase_add_test(tc, movement_xyz_0);

  return tc;
}

static TCase *scaling_tc(void) {
  TCase *tc = tcase_create("scaling");
  tcase_add_test(tc, scale_positive);
  tcase_add_test(tc, scale_negative);
  
  return tc;
}

Suite *affine_suite() {
  Suite *s = suite_create("affine_suite");

  suite_add_tcase(s, rotations_tc());
  suite_add_tcase(s, movement_tc());
  suite_add_tcase(s, scaling_tc());

  return s;
}

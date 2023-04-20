#include <check.h>
#include "../core/pars.h"

#define TEST_EPS 1e-6

/* ### EXPECTED SECTION ### */
static int count_vertex_expected = 8;
/* static int count_side_expected = 12; */
static int size_sort_array_expected = 6 * 2 * 3 * 4;
/* static int size_unsort_memory_expected; */
/* static int size_sort_memory_expected; */
/* static const float vertices_expected[] = { */
/*     -1.480759, 1.795634, 1.982020,  1.0, -1.097703, -2.336702, -0.361380, 1.0, */
/*     -4.594137, 3.352988, -1.273126, 1.0, -4.211081, -0.779347, -3.616526, 1.0, */
/*     2.107359,  3.588090, -0.592267, 1.0, 2.490416,  -0.544245, -2.935667, 1.0, */
/*     -1.006018, 5.145445, -3.847413, 1.0, -0.622962, 1.013109,  -6.190813, 1.0, */
/* }; */
/* static const int faces_expected[] = { */
/*     0, 4, 6, 0, 6, 2, 3, 2, 6, 3, 6, 7, 7, 6, 4, 7, 4, 5, */
/*     5, 1, 3, 5, 3, 7, 1, 0, 2, 1, 2, 3, 5, 4, 0, 5, 0, 1, */
/* }; */
/* ### END OF EXPECTED FUNCTION ### */

/* ### SERVICE PROCEDURES ### */
static float *model_array = NULL;
static FILE *obj_file = NULL;
static Pars_counters *test_view = NULL;

static void simple_cube_setup(void) {
  test_view = calloc(1, sizeof(Pars_counters));
  obj_file = fopen("../data-samples/cube_simple.obj", "r");
  model_array = array_sort(obj_file, test_view);
}

static void non_existent_setup(void) {
  test_view = calloc(1, sizeof(Pars_counters));
  /* model_array = array_sort("aboba.obj", test_view); */
}

static void test_teardown(void) {
  if (obj_file) {
    fclose(obj_file);
    obj_file = NULL;
  }
  if (model_array) {
    free(model_array);
    model_array = NULL;
  }
  if (test_view) {
    free(test_view);
    test_view = NULL;
  }
}
/* ### END OF SERVICE PROCEDURES ### */

/* ## Check length of vertex array ## */
START_TEST(test_simple_cube_vertices_len) {
  ck_assert_uint_eq(test_view->count_vertex, count_vertex_expected);
}
END_TEST

/* ## Check length of sorted array ## */
START_TEST(test_simple_cube_sorted_array_len) {
  ck_assert_uint_eq(test_view->size_sort_array, size_sort_array_expected);
}
END_TEST
/* START_TEST(test_simple_cube_vertices_data) { */
  /* ck_assert_float_eq_tol(data[_i * 4], sc_vertices_expected[_i * 4], TEST_EPS); */
  /* ck_assert_float_eq_tol(data[_i * 4 + 1], sc_vertices_expected[_i * 4 + 1], */
  /*                        TEST_EPS); */
  /* ck_assert_float_eq_tol(data[_i * 4 + 2], sc_vertices_expected[_i * 4 + 2], */
  /*                        TEST_EPS); */
  /* ck_assert_float_eq_tol(data[_i * 4 + 3], 1.0, TEST_EPS); */
/* } */
/* END_TEST */

/* ## Check wrong file handler ## */
START_TEST(test_open_nonexistent_file) {
  ck_assert_ptr_null(model_array);
}
END_TEST

/* ### AGREGATED TEST CASE HANDLERS ### */
static TCase *simple_cube_tc(void) {
  TCase *tc = tcase_create("simple_cube");
  tcase_add_unchecked_fixture(tc, simple_cube_setup, test_teardown);
  tcase_add_test(tc, test_simple_cube_vertices_len);
  tcase_add_test(tc, test_simple_cube_sorted_array_len);
  /* check amount of faces */
  /* check parsed array */

  return tc;
}

static TCase *non_existent_file_tc(void) {
  TCase *tc = tcase_create("nonexistent_file");
  tcase_add_unchecked_fixture(tc, non_existent_setup, test_teardown);
  tcase_add_test(tc, test_open_nonexistent_file);

  return tc;
}
/* ### END OF AGREGATED TEST CASE HANDLERS ### */

Suite *obj_parser_suite() {
  Suite *s = suite_create("obj_parser_suite");

  suite_add_tcase(s, simple_cube_tc());
  suite_add_tcase(s, non_existent_file_tc());

  return s;
}

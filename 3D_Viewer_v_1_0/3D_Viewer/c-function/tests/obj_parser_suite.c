#include <check.h>

#include "../core/pars.h"

#define TEST_EPS 1e-6

/* ### EXPECTED SECTION ### */
static int count_vertex_expected = 9;
static int size_sort_array_expected = 6 * 2 * 3 * 4;
/* ### END OF EXPECTED FUNCTION ### */

/* ### SERVICE PROCEDURES ### */
static FILE *obj_file = NULL;
static Pars_counters *test_view = NULL;

static void simple_cube_setup(void) {
  test_view = calloc(1, sizeof(Pars_counters));
  obj_file = fopen("3D_Viewer/c-function/tests/cube_simple.obj", "r");
  array_sort(obj_file, test_view);
}

static void non_existent_setup(void) {
  test_view = calloc(1, sizeof(Pars_counters));
  obj_file = fopen("aboba.obj", "r");
  array_sort(obj_file, test_view);
}

static void test_teardown(void) {
  if (obj_file) {
    fclose(obj_file);
    obj_file = NULL;
  }
  if (test_view->sorted_array) {
    free(test_view->sorted_array);
    test_view->sorted_array = NULL;
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

/* ## Check wrong file handler ## */
START_TEST(test_open_nonexistent_file) {
  ck_assert_ptr_null(test_view->sorted_array);
}
END_TEST

/* ### AGREGATED TEST CASE HANDLERS ### */
static TCase *simple_cube_tc(void) {
  TCase *tc = tcase_create("simple_cube");
  tcase_add_unchecked_fixture(tc, simple_cube_setup, test_teardown);
  tcase_add_test(tc, test_simple_cube_vertices_len);
  tcase_add_test(tc, test_simple_cube_sorted_array_len);

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

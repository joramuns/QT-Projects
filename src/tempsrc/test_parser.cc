#include "parser.h"

void wrong_filename() {
  s21::Parser test("cube.obj");
  std::cout << "Success" << std::endl;
}

void true_filename() {
  s21::Parser test("../../data-samples/test_one.obj");
  std::cout << "Success" << std::endl;
}


int main() {
  std::cout << "test 1:" << std::endl;
  wrong_filename();
  std::cout << "test 2:" << std::endl;
  true_filename();

  return 0;
}

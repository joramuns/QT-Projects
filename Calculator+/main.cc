#include "main.h"
#include <iomanip>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  double op = 91.9;
  s21::Element test(op);
  op = 13.888888;
  s21::Element oist(op);
  s21::Converter keka;
  keka.AddOperand(test);
  keka.AddOperand(oist);
  std::cout << std::setprecision(15) << keka;
  return 0;
}

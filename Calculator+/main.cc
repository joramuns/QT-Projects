#include "main.h"
#include <iomanip>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  double num1 = 1;
  double num2 = 2;
  double num3 = 3;
  double num4 = 4;
  double num5 = 5;
  s21::Element enum1(num1);
  s21::Element enum2(num2);
  s21::Element enum3(num3);
  s21::Element enum4(num4);
  s21::Element enum5(num5);
  s21::Element znakmin(s21::Element::kSubtraction);
  s21::Element znakplu(s21::Element::kAddition);
  s21::Element znakumn(s21::Element::kMultiplication);
  s21::Element znakdel(s21::Element::kDivision);
  s21::Element znakosk(s21::Element::kBracketOpen);
  s21::Element znakzsk(s21::Element::kBracketClose);
  s21::Element znakste(s21::Element::kPower);
  s21::Converter keka;

  keka.AddOperand(enum3);
  keka.AddOperator(znakplu);
  keka.AddOperand(enum4);
  keka.AddOperator(znakumn);
  keka.AddOperand(enum2);
  keka.AddOperator(znakdel);
  keka.AddOperator(znakosk);
  keka.AddOperand(enum1);
  keka.AddOperator(znakmin);
  keka.AddOperand(enum5);
  keka.AddOperator(znakzsk);
  keka.AddOperator(znakste);
  keka.AddOperand(enum2);
  keka.AddOperator(znakste);
  keka.AddOperand(enum3);

  keka.Finalize();
  std::cout << std::setprecision(15) << keka;
  return 0;
}

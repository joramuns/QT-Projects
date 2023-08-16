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
  enum2.AppendNumber(3);
  s21::Element enum3(num3);
  s21::Element enum4(num4);
  enum4.AppendNumber(3, 1);
  enum4.AppendNumber(3, 3);

  s21::Element enum5(num5);
  s21::Element znakmin(s21::Element::kSubtraction);
  s21::Element znakplu(s21::Element::kAddition);
  s21::Element znakumn(s21::Element::kMultiplication);
  s21::Element znakdel(s21::Element::kDivision);
  s21::Element znakosk(s21::Element::kBracketOpen);
  s21::Element znakzsk(s21::Element::kBracketClose);
  s21::Element znakste(s21::Element::kPower);
  s21::Model keka;

  keka.AddElement(enum3);
  keka.AddElement(znakplu);
  keka.AddElement(enum4);
  keka.AddElement(znakumn);
  keka.AddElement(enum2);
  keka.AddElement(znakdel);
  keka.AddElement(znakosk);
  keka.AddElement(enum1);
  keka.AddElement(znakmin);
  keka.AddElement(enum5);
  keka.AddElement(znakzsk);
  keka.AddElement(znakste);
  keka.AddElement(enum2);
  keka.AddElement(znakste);
  keka.AddElement(enum3);
  keka.Convert();

  keka.OutputModel();

  return 0;
}

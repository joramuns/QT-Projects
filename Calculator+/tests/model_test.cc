#include <gtest/gtest.h>

#include "../model/model.h"

class ModelTest : public ::testing::Test {
  using OpType = s21::Element::OperatorType;

 protected:
  void SetUp() override {}
  s21::Element e_plus{OpType::kAddition};
  s21::Element e_minus{OpType::kSubtraction};
  s21::Element e_mod{OpType::kModulus};
  s21::Element e_multiply{OpType::kMultiplication};
  s21::Element e_divide{OpType::kDivision};

  s21::Element e_sin{OpType::kSin};
  s21::Element e_cos{OpType::kCos};
  s21::Element e_tan{OpType::kTan};
  s21::Element e_asin{OpType::kAsin};
  s21::Element e_acos{OpType::kAcos};
  s21::Element e_atan{OpType::kAtan};
  s21::Element e_sqrt{OpType::kSqrt};
  s21::Element e_ln{OpType::kLn};
  s21::Element e_log{OpType::kLog};
  s21::Element e_power{OpType::kPower};

  s21::Element e_open_bracket{OpType::kBracketOpen};
  s21::Element e_close_bracket{OpType::kBracketClose};

  s21::Element e_1{1.0};
  s21::Element e_2{2.0};
  s21::Element e_3{3.0};
  s21::Element e_4{4.0};
  s21::Element e_5{5.0};
  s21::Element e_6{6.0};
  s21::Element e_7{7.0};
  s21::Element e_8{8.0};
  s21::Element e_9{9.0};

  s21::Model test_model;
};

TEST_F(ModelTest, n_1) {
  /* 4 + 4 * 2 / ( 1 - 5 ) = 2*/
  test_model.AddElement(e_4);
  test_model.AddElement(e_plus);
  test_model.AddElement(e_4);
  test_model.AddElement(e_multiply);
  test_model.AddElement(e_2);
  test_model.AddElement(e_divide);
  test_model.AddElement(e_open_bracket);
  test_model.AddElement(e_1);
  test_model.AddElement(e_minus);
  test_model.AddElement(e_5);
  test_model.AddElement(e_close_bracket);

  test_model.Convert();
  double result = test_model.Evaluate();
  ASSERT_DOUBLE_EQ(result, 2.0);
  test_model.ClearModel();
}

TEST_F(ModelTest, n_2) {
   /* 4 + 4 * 2 / 1 - 5 = 7 */
  test_model.AddElement(e_4);
  test_model.AddElement(e_plus);
  test_model.AddElement(e_4);
  test_model.AddElement(e_multiply);
  test_model.AddElement(e_2);
  test_model.AddElement(e_divide);
  test_model.AddElement(e_1);
  test_model.AddElement(e_minus);
  test_model.AddElement(e_5);

  test_model.Convert();
  double result = test_model.Evaluate();
  ASSERT_DOUBLE_EQ(result, 7.0);
  test_model.ClearModel();
}

TEST_F(ModelTest, n_3) {
  /* 4 + 4 * ( 2 / 1 - 5 ) = -8 */
  test_model.AddElement(e_4);
  test_model.AddElement(e_plus);
  test_model.AddElement(e_4);
  test_model.AddElement(e_multiply);
  test_model.AddElement(e_open_bracket);
  test_model.AddElement(e_2);
  test_model.AddElement(e_divide);
  test_model.AddElement(e_1);
  test_model.AddElement(e_minus);
  test_model.AddElement(e_5);
  test_model.AddElement(e_close_bracket);

  test_model.Convert();
  double result = test_model.Evaluate();
  ASSERT_DOUBLE_EQ(result, -8.0);
  test_model.ClearModel();
}

/*   double num1 = 1; */
/*   double num2 = 2; */
/*   double num3 = 3; */
/*   double num4 = 4; */
/*   double num5 = 5; */
/*   s21::Element enum1(num1); */
/*   s21::Element enum2(num2); */
/*   enum2.AppendNumber(3); */
/*   s21::Element enum3(num3); */
/*   s21::Element enum4(num4); */
/*   enum4.AppendNumber(3, 1); */
/*   enum4.AppendNumber(3, 3); */

/*   s21::Element enum5(num5); */
/*   s21::Element znakmin(s21::Element::kSubtraction); */
/*   s21::Element znakplu(s21::Element::kAddition); */
/*   s21::Element znakumn(s21::Element::kMultiplication); */
/*   s21::Element znakdel(s21::Element::kDivision); */
/*   s21::Element znakosk(s21::Element::kBracketOpen); */
/*   s21::Element znakzsk(s21::Element::kBracketClose); */
/*   s21::Element znakste(s21::Element::kPower); */
/*   s21::Element znaksin(s21::Element::kSin); */
/*   s21::Model keka; */

/*   keka.AddElement(enum3); */
/*   keka.AddElement(znakplu); */
/*   keka.AddElement(enum4); */
/*   keka.AddElement(znakumn); */
/*   keka.AddElement(enum2); */
/*   keka.AddElement(znakdel); */
/*   keka.AddElement(znaksin); */
/*   keka.AddElement(znakosk); */
/*   keka.AddElement(enum1); */
/*   keka.AddElement(znakmin); */
/*   keka.AddElement(enum5); */
/*   keka.AddElement(znakzsk); */
/*   keka.AddElement(znakste); */
/*   keka.AddElement(enum2); */
/*   keka.AddElement(znakste); */
/*   keka.AddElement(enum3); */
/*   keka.Convert(); */

/*   keka.OutputModel(); */
/*   std::cout << std::endl; */
/*   double res = keka.Evaluate(); */

#include "test_main.h"

class ModelTest : public ::testing::Test {
 public:
  using OpType = s21::Element::OperatorType;

 protected:
  void SetUp() override {}
  s21::Model test_model;
};

/* 4 + 4 * 2 / ( 1 - 5 ) = 2 */
TEST_F(ModelTest, n_1) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 4.0 + 4.0 * 2.0 / (1.0 - 5.0);
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 4 + 4 * 2 / 1 - 5 = 7 */
TEST_F(ModelTest, n_2) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 4.0 + 4.0 * 2.0 / 1.0 - 5.0;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 4 + 4 * ( 2 / 1 - 5 ) = -8 */
TEST_F(ModelTest, n_3) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 4.0 + 4.0 * (2.0 / 1.0 - 5.0);
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 4 + ( 4 * 2 / 1 - 5 ) = 7 */
TEST_F(ModelTest, n_4) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 4.0 + (4.0 * 2.0 / 1.0 - 5.0);
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 4 + 4 * ( 2 /  1 ) - 5 = 7 */
TEST_F(ModelTest, n_5) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 4.0 + 4.0 * (2.0 / 1.0) - 5.0;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 4 + ( 4 * 2 / 1 ) - 5 = 7 */
TEST_F(ModelTest, n_6) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 4.0 + (4.0 * 2.0 / 1.0) - 5.0;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* ( 4 + 4 * 2 / 1 ) - 5 = 7 */
TEST_F(ModelTest, n_7) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = (4.0 + 4.0 * 2.0 / 1.0) - 5.0;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 4 + ( 4 * 2 ) / 1 - 5 = 7 */
TEST_F(ModelTest, n_8) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 4.0 + (4.0 * 2.0) / 1.0 - 5.0;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* ( 4 + 4 * 2 ) / 1 - 5 = 7 */
TEST_F(ModelTest, n_9) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = (4.0 + 4.0 * 2.0) / 1.0 - 5.0;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 8 * (7 + 6 * 4) + 3 = 251 */
TEST_F(ModelTest, n_10) {
  test_model.AddElement('8');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('7');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('6');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('3');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 8.0 * (7.0 + 6.0 * 4.0) + 3.0;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 2 / (3 + 2) * 5 = 2 */
TEST_F(ModelTest, n_11) {
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('5');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 2.0 / (3.0 + 2.0) * 5.0;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 2+9.3-8^3/4+56.2 = -60.5 */
TEST_F(ModelTest, n_12) {
  test_model.AddElement('2');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('9');
  test_model.AddElement('.');
  test_model.AddElement('3');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('8');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('5');
  test_model.AddElement('6');
  test_model.AddElement('.');
  test_model.AddElement('2');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 2.0 + 9.3 - pow(8.0, 3.0) / 4.0 + 56.2;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 2+9.3-8^3/(4+56.2) = 2.795017 */
TEST_F(ModelTest, n_13) {
  test_model.AddElement('2');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('9');
  test_model.AddElement('.');
  test_model.AddElement('3');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('8');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('5');
  test_model.AddElement('6');
  test_model.AddElement('.');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 2.0 + 9.3 - pow(8.0, 3.0) / (4.0 + 56.2);
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 2^3^2 = 512 */
TEST_F(ModelTest, n_14) {
  test_model.AddElement('2');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('2');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = pow(2.0, pow(3.0, 2.0));
  ASSERT_DOUBLE_EQ(result, expect);
  ASSERT_DOUBLE_EQ(result, 512.0);
  test_model.ClearModel();
}

/* 2^(3^2) = 512 */
TEST_F(ModelTest, n_15) {
  test_model.AddElement('2');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = pow(2.0, pow(3.0, 2.0));
  ASSERT_DOUBLE_EQ(result, expect);
  ASSERT_DOUBLE_EQ(result, 512.0);
  test_model.ClearModel();
}

/* (2^3)^2 = 64 */
TEST_F(ModelTest, n_16) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('2');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = pow(pow(2.0, 3.0), 2.0);
  ASSERT_DOUBLE_EQ(result, expect);
  ASSERT_DOUBLE_EQ(result, 64.0);
  test_model.ClearModel();
}

/* cos(431.2*2^2/8) = -0.390250 */
TEST_F(ModelTest, n_17) {
  test_model.AddElement(OpType::kCos);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('4');
  test_model.AddElement('3');
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('8');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = cos(431.2 * pow(2.0, 2.0) / 8.0);
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 3*sin(4+5) = 1.236355 */
TEST_F(ModelTest, n_18) {
  test_model.AddElement('3');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kSin);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('5');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 3.0 * sin(4.0 + 5.0);
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 431.2*2^2/8 = 215.6 */
TEST_F(ModelTest, n_19) {
  test_model.AddElement('4');
  test_model.AddElement('3');
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('8');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 431.2 * pow(2.0, 2.0) / 8.0;
  ASSERT_DOUBLE_EQ(result, expect);
  ASSERT_DOUBLE_EQ(result, 215.6);
  test_model.ClearModel();
}

/* cos(sin(2+9*6^1.2-tan(1))) = 0.742186 */
TEST_F(ModelTest, n_20) {
  test_model.AddElement(OpType::kCos);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement(OpType::kSin);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('2');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('9');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('6');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kTan);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = cos(sin(2.0 + 9.0 * pow(6.0, 1.2) - tan(1.0)));
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* sqrt(cos(sin(2+9*6^1.2-tan(1)))) */
TEST_F(ModelTest, n_21) {
  test_model.AddElement(OpType::kSqrt);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement(OpType::kCos);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement(OpType::kSin);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('2');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('9');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('6');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kTan);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = sqrt(cos(sin(2.0 + 9.0 * pow(6.0, 1.2) - tan(1.0))));
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* sqrt(cos(sin(2+9*6^1.2-tan(1))))mod0.1 = 0.06150001881 */
TEST_F(ModelTest, n_22) {
  test_model.AddElement(OpType::kSqrt);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement(OpType::kCos);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement(OpType::kSin);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('2');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('9');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('6');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kTan);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kModulus);
  test_model.AddElement('0');
  test_model.AddElement('.');
  test_model.AddElement('1');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect =
      fmod(sqrt(cos(sin(2.0 + 9.0 * pow(6.0, 1.2) - tan(1.0)))), 0.1);
  ASSERT_NEAR(result, expect, 1e-15);
  test_model.ClearModel();
}

/* sqrt(2^2)*5/(4-3mod2)*(4-sqrt(9*9)) = -16.666667 */
TEST_F(ModelTest, n_23) {
  test_model.AddElement(OpType::kSqrt);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('2');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('5');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kModulus);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kSqrt);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('9');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('9');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = sqrt(pow(2.0, 2.0)) * 5.0 / (4.0 - fmod(3.0, 2.0)) *
                  (4.0 - sqrt(9.0 * 9.0));
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* cos(1/3)*sin(1.352^9/(4+3)) = 0.787603 */
TEST_F(ModelTest, n_24) {
  test_model.AddElement(OpType::kCos);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kSin);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('3');
  test_model.AddElement('5');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('9');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = cos(1.0 / 3.0) * sin(pow(1.352, 9.0) / (4.0 + 3.0));
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* (cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150) = 0.022386 */
TEST_F(ModelTest, n_25) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement(OpType::kCos);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kSin);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('3');
  test_model.AddElement('5');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('9');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement('7');
  test_model.AddElement('6');
  test_model.AddElement('.');
  test_model.AddElement('5');
  test_model.AddElement('6');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kLog);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement('5');
  test_model.AddElement('0');
  test_model.AddElement('.');
  test_model.AddElement('0');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect =
      (cos(1.0 / 3.0) * sin(pow(1.352, 9.0) / (4.0 + 3.0)) / 76.56) *
      log10(150);
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* sqrt(cos(sin(2+9*6^1.2-tan(1)))) */
TEST_F(ModelTest, n_26) {
  test_model.AddElement(OpType::kSqrt);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement(OpType::kCos);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement(OpType::kSin);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('2');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('9');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('6');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kTan);
  /* test_model.AddElement(OpType::kBracketOpen); */
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = sqrt(cos(sin(2.0 + 9.0 * pow(6.0, 1.2) - tan(1.0))));
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* -1-(-1) */
TEST_F(ModelTest, n_27) {
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = -1 - (-1);
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* -1-(-(+1)) */
TEST_F(ModelTest, n_28) {
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = -1 - (-(+1));
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 1e2 = 100 */
TEST_F(ModelTest, n_29) {
  test_model.AddElement('1');
  test_model.AddElement('e');
  test_model.AddElement('2');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 1e2;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 0.1e2 = 10 */
TEST_F(ModelTest, n_30) {
  test_model.AddElement('0');
  test_model.AddElement('.');
  test_model.AddElement('1');
  test_model.AddElement('e');
  test_model.AddElement('2');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 0.1e2;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 100e-2 = 1 */
TEST_F(ModelTest, n_31) {
  test_model.AddElement('1');
  test_model.AddElement('0');
  test_model.AddElement('0');
  test_model.AddElement('e');
  test_model.AddElement('e');
  test_model.AddElement('e');
  test_model.AddElement('2');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 100e-2;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 100e-2 = 1 */
TEST_F(ModelTest, n_32) {
  test_model.AddElement('1');
  test_model.AddElement('0');
  test_model.AddElement('0');
  test_model.AddElement('e');
  test_model.AddElement('e');
  test_model.AddElement('.');
  test_model.AddElement('e');
  test_model.AddElement('2');
  test_model.AddElement('.');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 100e-2;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* asin(5*(4^(3+2*2)-0.03e+3)*1e-5)+acos(ln(10)*2e-2)-atan(0.04) */
TEST_F(ModelTest, n_33) {
  test_model.AddElement(OpType::kAsin);
  test_model.AddElement('5');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kPower);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('0');
  test_model.AddElement('.');
  test_model.AddElement('0');
  test_model.AddElement('3');
  test_model.AddElement('e');
  test_model.AddElement('e');
  test_model.AddElement('3');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('1');
  test_model.AddElement('e');
  test_model.AddElement('e');
  test_model.AddElement('e');
  test_model.AddElement('5');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement(OpType::kAcos);
  test_model.AddElement(OpType::kLn);
  test_model.AddElement('1');
  test_model.AddElement('0');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement('e');
  test_model.AddElement('e');
  test_model.AddElement('e');
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement(OpType::kAtan);
  test_model.AddElement('0');
  test_model.AddElement('.');
  test_model.AddElement('0');
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = asin(5.0 * (pow(4.0, (3.0 + 2.0 * 2.0)) - 0.03e+3) * 1e-5) +
                  acos(log(10.0) * 2e-2) - atan(0.04);
  ASSERT_DOUBLE_EQ(result, expect);

  std::string string_result = test_model.GetResult();
  std::string string_expect =
      "asin ( 5 \u00D7 ( 4 ^ ( 3 \u002B 2 \u00D7 2 ) \u2212 0.03e+3 ) \u00D7 "
      "1e-5 ) \u002B acos ( ln ( 10 ) \u00D7 2e-2 ) \u2212 atan ( 0.04 )  = "
      "2.442154";
  ASSERT_EQ(string_result, string_expect);
  test_model.ClearModel();
}

/* .e1 */
TEST_F(ModelTest, n_34) {
  test_model.AddElement('.');
  test_model.AddElement('e');
  test_model.AddElement('1');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 0.e1;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* 1.e111 = 1.0e11 */
TEST_F(ModelTest, n_35) {
  test_model.AddElement('1');
  test_model.AddElement('.');
  test_model.AddElement('e');
  test_model.AddElement('1');
  test_model.AddElement('1');
  test_model.AddElement('1');

  int validator = test_model.ValidateExpr();
  EXPECT_EQ(validator, 0);

  double result = test_model.Evaluate();
  double expect = 1.e11;
  ASSERT_DOUBLE_EQ(result, expect);
  test_model.ClearModel();
}

/* -1+2mod3*4/sin(cos(tan(5))) */
TEST_F(ModelTest, n_36) {
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kModulus);
  test_model.AddElement('3');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kDivision);
  test_model.AddElement(OpType::kSin);
  test_model.AddElement(OpType::kCos);
  test_model.AddElement(OpType::kTan);
  test_model.AddElement('5');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);

  std::string result = test_model.GetResult();
  std::string expect =
      "\u2212 1 \u002B 2 mod 3 \u00D7 4 \u00F7 sin ( cos ( tan ( 5 ) ) )  = "
      "-10.687746";
  ASSERT_EQ(result, expect);
  test_model.ClearModel();
}

/* x */
TEST_F(ModelTest, n_37) {
  test_model.AddElement('x');
  std::vector<double> bounds{-100.0, 100.0, -100.0, 100.0};

  auto coords = test_model.GetCoordinates(bounds);

  auto x_iter = coords.first.begin();
  auto x_end_iter = coords.first.end();
  auto y_iter = coords.first.begin();
  auto y_end_iter = coords.first.end();
  while (++x_iter != x_end_iter && ++y_iter != y_end_iter) {
    ASSERT_DOUBLE_EQ(*x_iter, *y_iter);
  }
  test_model.ClearModel();
}

/* log(10)^sqrt(4) */
TEST_F(ModelTest, n_38) {
  test_model.AddElement(OpType::kLog);
  test_model.AddElement('1');
  test_model.AddElement('0');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kPower);
  test_model.AddElement(OpType::kSqrt);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketClose);

  std::string result = test_model.GetResult();
  std::string expect = "log ( 10 ) ^ sqrt ( 4 )  = 1";
  ASSERT_EQ(result, expect);
  test_model.ClearModel();
}

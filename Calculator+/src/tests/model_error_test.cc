#include "test_main.h"

class FailTest : public ::testing::Test {
 public:
  using OpType = s21::Element::OperatorType;

 protected:
  void SetUp() override {}
  s21::Model test_model;
};

/* 4+4*2(1-5) */
TEST_F(FailTest, n_1) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('2');
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('1');
  test_model.AddElement(OpType::kSubtraction);
  test_model.AddElement('5');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_2) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement('4');

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_3) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_4) {
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('4');

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_5) {
  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_6) {
  test_model.AddElement(OpType::kAddition);

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_7) {
  test_model.AddElement('4');
  test_model.AddElement('x');

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_8) {
  test_model.AddElement('x');
  test_model.AddElement('4');

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_9) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_10) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement('4');

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_11) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketClose);
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_12) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_13) {
  test_model.AddElement(OpType::kBracketOpen);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('4');
  test_model.AddElement(OpType::kBracketClose);

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

TEST_F(FailTest, n_14) {
  test_model.AddElement('4');
  test_model.AddElement(OpType::kAddition);
  test_model.AddElement(OpType::kMultiplication);
  test_model.AddElement('4');

  int validator = test_model.ValidateExpr();
  ASSERT_NE(validator, 0);
  test_model.ClearModel();
}

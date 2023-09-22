#include "test_main.h"

class CreditTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  s21::Model credit_model;
};

TEST_F(CreditTest, n_1) {
  double amount = 10000.0;
  double term = 7.0;
  double rate = 2.0;
  int type = 0;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 66.77;
  double expect_totalpayment = 10066.77;
  double expect_payment = 1438.11;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, n_2) {
  double amount = 253987.0;
  double term = 31.0;
  double rate = 3.78;
  int type = 0;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 13002.36;
  double expect_totalpayment = 266989.36;
  double expect_payment = 8612.56;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, n_3) {
  double amount = 0.01;
  double term = 77.0;
  double rate = 0.1;
  int type = 0;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 0.0;
  double expect_totalpayment = 0.01;
  double expect_payment = 0.0;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, n_4) {
  double amount = 99818.0;
  double term = 77.0;
  double rate = 0.01;
  int type = 0;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 32.52;
  double expect_totalpayment = 99850.52;
  double expect_payment = 1296.76;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, n_5) {
  double amount = 100.0;
  double term = 10.0;
  double rate = 0.0;
  int type = 0;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 0.0;
  double expect_totalpayment = 100.0;
  double expect_payment = 10.0;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, d_1) {
  double amount = 10000.0;
  double term = 7.0;
  double rate = 2.0;
  int type = 1;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 66.67;
  double expect_totalpayment = 10066.67;
  double expect_payment = 1445.24;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, d_2) {
  double amount = 253987.0;
  double term = 31.0;
  double rate = 3.78;
  int type = 1;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 12800.94;
  double expect_totalpayment = 266787.94;
  double expect_payment = 8993.19;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, d_3) {
  double amount = 90.71;
  double term = 63.0;
  double rate = 11.2;
  int type = 1;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 27.09;
  double expect_totalpayment = 117.8;
  double expect_payment = 2.29;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, d_4) {
  double amount = 99818.0;
  double term = 77.0;
  double rate = 0.01;
  int type = 1;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 32.44;
  double expect_totalpayment = 99850.44;
  double expect_payment = 1297.17;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

TEST_F(CreditTest, d_5) {
  double amount = 0.01;
  double term = 77.0;
  double rate = 0.5;
  int type = 0;
  credit_model.credit_model_.SetData(amount, term, rate, type);
  credit_model.credit_model_.Calculate();

  double overpayment = credit_model.credit_model_.GetOverpayment();
  double totalpayment = credit_model.credit_model_.GetTotalPayment();
  auto payments = credit_model.credit_model_.GetPayments();

  double expect_overpayment = 0.0;
  double expect_totalpayment = 0.01;
  double expect_payment = 0.0;
  ASSERT_NEAR(overpayment, expect_overpayment, 1e-2);
  ASSERT_NEAR(totalpayment, expect_totalpayment, 1e-2);
  ASSERT_NEAR(payments[0], expect_payment, 1e-2);
}

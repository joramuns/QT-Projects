#include "test_main.h"

class DepositTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  s21::Model model;
};

TEST_F(DepositTest, n_1) {
  double amount = 10000.0;
  int term = 7;
  double rate = 3.3;
  double tax = 0.13;
  int periodicity = 30;
  bool capitalization = false;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);

  model.deposit_model_.EvaluateDeposit();
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();

  double expect_total_profit = 6.33;
  double expect_tax_amount = 0.83;
  double expect_end_amount = 10000.0;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
}

TEST_F(DepositTest, n_2) {
  double amount = 10000.0;
  int term = 30;
  double rate = 3.3;
  double tax = 0.13;
  int periodicity = 30;
  bool capitalization = true;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);

  model.deposit_model_.EvaluateDeposit();
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();

  double expect_total_profit = 27.12;
  double expect_tax_amount = 3.52;
  double expect_end_amount = 10027.12;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
}

TEST_F(DepositTest, n_3) {
  double amount = 329789.0;
  int term = 30;
  double rate = 7.23;
  double tax = 0.04;
  int periodicity = 30;
  bool capitalization = true;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);
  model.deposit_model_.AddReplenishment(10.0, 12345.0);
  model.deposit_model_.AddWithdrawal(12.0, 84327.0);

  model.deposit_model_.EvaluateDeposit();
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();

  double expect_total_profit = 1693.74;
  double expect_tax_amount = 67.75;
  double expect_end_amount = 259500.74;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
}

TEST_F(DepositTest, n_4) {
  double amount = 329789.0;
  int term = 30;
  double rate = 7.23;
  double tax = 0.00;
  int periodicity = 30;
  bool capitalization = true;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);
  model.deposit_model_.AddReplenishment(10.0, 12345.0);
  model.deposit_model_.AddReplenishment(12.0, 12345.0);
  model.deposit_model_.RemoveReplenishment(1);
  model.deposit_model_.RemoveReplenishment(0);
  model.deposit_model_.AddWithdrawal(12.0, 84327.0);
  model.deposit_model_.AddWithdrawal(14.0, 84327.0);
  model.deposit_model_.RemoveWithdrawal(1);
  model.deposit_model_.RemoveWithdrawal(0);

  model.deposit_model_.EvaluateDeposit();
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();

  double expect_total_profit = 1959.76;
  double expect_tax_amount = 0.0;
  double expect_end_amount = 331748.76;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
}

TEST_F(DepositTest, n_5) {
  double amount = 184728.12;
  int term = 40;
  double rate = 3.97;
  double tax = 0.00;
  int periodicity = 30;
  bool capitalization = false;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);
  model.deposit_model_.AddReplenishment(10.0, 12345.0);
  model.deposit_model_.AddReplenishment(12.0, 12345.0);
  auto replenishments = model.deposit_model_.GetReplenishmentList();
  for (const auto &item : replenishments) {
    ASSERT_DOUBLE_EQ(item.second, 12345.0);
  }
  model.deposit_model_.RemoveReplenishment(1);
  model.deposit_model_.RemoveReplenishment(0);
  model.deposit_model_.AddWithdrawal(12.0, 84327.0);
  model.deposit_model_.AddWithdrawal(14.0, 84327.0);
  auto withdrawals = model.deposit_model_.GetWithdrawalList();
  for (const auto &item : withdrawals) {
    ASSERT_DOUBLE_EQ(item.second, 84327.0);
  }
  model.deposit_model_.RemoveWithdrawal(1);
  model.deposit_model_.RemoveWithdrawal(0);
  model.deposit_model_.AddWithdrawal(14.0, amount + 100000.0);

  model.deposit_model_.EvaluateDeposit();
  withdrawals = model.deposit_model_.GetWithdrawalList();
  ASSERT_TRUE(withdrawals.empty());
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();
  auto payoffs = model.deposit_model_.GetPayoffsList();

  double expect_total_profit = 803.69;
  double expect_tax_amount = 0.0;
  double expect_end_amount = 184728.12;
  double expect_first_payoff = 602.77;
  double expect_last_payoff = 200.92;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
  ASSERT_NEAR(payoffs.front(), expect_first_payoff, 1e-2);
  ASSERT_NEAR(payoffs.back(), expect_last_payoff, 1e-2);
}

TEST_F(DepositTest, n_6) {
  double amount = 20000.0;
  int term = 15;
  double rate = 1.5;
  double tax = 0.0;
  int periodicity = 30;
  bool capitalization = false;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);

  model.deposit_model_.EvaluateDeposit();
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();

  double expect_total_profit = 12.33;
  double expect_tax_amount = 0.0;
  double expect_end_amount = 20000.0;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
}

TEST_F(DepositTest, n_7) {
  double amount = 20000.0;
  int term = 15;
  double rate = 1.5;
  double tax = 0.0;
  int periodicity = 30;
  bool capitalization = true;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);

  model.deposit_model_.EvaluateDeposit();
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();

  double expect_total_profit = 12.33;
  double expect_tax_amount = 0.0;
  double expect_end_amount = 20012.33;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
}

TEST_F(DepositTest, n_8) {
  double amount = 9325.76;
  int term = 1;
  double rate = 10;
  double tax = 0.0;
  int periodicity = 30;
  bool capitalization = false;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);

  model.deposit_model_.EvaluateDeposit();
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();

  double expect_total_profit = 2.56;
  double expect_tax_amount = 0.0;
  double expect_end_amount = 9325.76;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
}

TEST_F(DepositTest, n_9) {
  double amount = 9727.25;
  int term = 1;
  double rate = 10;
  double tax = 0.0;
  int periodicity = 30;
  bool capitalization = false;
  model.deposit_model_.SetDepositData(amount, term, rate);
  model.deposit_model_.SetDepositType(tax, periodicity, capitalization);

  model.deposit_model_.EvaluateDeposit();
  double total_profit = model.deposit_model_.GetTotalProfit();
  double tax_amount = model.deposit_model_.GetTaxCharge();
  double end_amount = model.deposit_model_.GetEndAmount();

  double expect_total_profit = 2.67;
  double expect_tax_amount = 0.0;
  double expect_end_amount = 9727.25;
  ASSERT_NEAR(total_profit, expect_total_profit, 1e-2);
  ASSERT_NEAR(tax_amount, expect_tax_amount, 1e-2);
  ASSERT_NEAR(end_amount, expect_end_amount, 1e-2);
}

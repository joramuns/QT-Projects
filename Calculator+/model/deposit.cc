#include "deposit.h"

namespace s21 {
DepositCalc::DepositCalc() {}

void DepositCalc::AddReplenishment(double day, double amount) noexcept {
  replenishments_[day] += amount;
}

void DepositCalc::RemoveReplenishment(int number) noexcept {
  auto iter = replenishments_.begin();
  for (int i = 0; i < number; ++i) {
    ++iter;
  }
  replenishments_.erase(iter);
}

void DepositCalc::AddWithdrawal(double day, double amount) noexcept {
  withdrawals_[day] += amount;
}

void DepositCalc::RemoveWithdrawal(int number) noexcept {
  auto iter = withdrawals_.begin();
  for (int i = 0; i < number; ++i) {
    ++iter;
  }
  withdrawals_.erase(iter);
}

void DepositCalc::SetDepositData(double amount, int term,
                                 double rate) noexcept {
  amount_ = amount;
  term_ = term;
  interest_rate_ = rate / 100.0;
}

void DepositCalc::SetDepositType(int periodicity,
                                 bool capitalization) noexcept {
  deposit_type_ = periodicity;
  capitalization_ = capitalization;
}

void DepositCalc::EvaluateDeposit() noexcept {
  payoffs_.clear();
  profit_amount_ = 0.0;
  end_amount_ = 0.0;
  tax_amount_ = 0.0;

  int payoffs_number = term_ / deposit_type_;
  if (payoffs_.capacity() < payoffs_number) {
    payoffs_.reserve(payoffs_number);
  }

  double daily_profit = (amount_ * interest_rate_) / 365.0;
  for (int day = 1; day <= term_; ++day) {
    profit_amount_ += daily_profit;
    if (day % deposit_type_ == 0 || day == term_) {
      payoffs_.push_back(profit_amount_);
      profit_amount_ = 0.0;
      if (capitalization_) {
        amount_ += payoffs_.back();
        daily_profit = (amount_ * interest_rate_) / 365.0;
      }
    }
  }
}

const std::map<double, double> &DepositCalc::GetReplenishmentList()
    const noexcept {
  return replenishments_;
}

const std::map<double, double> &DepositCalc::GetWithdrawalList()
    const noexcept {
  return withdrawals_;
}

const std::vector<double> &DepositCalc::GetPayoffsList() const noexcept {
  return payoffs_;
}

}  // namespace s21

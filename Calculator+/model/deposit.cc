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

const std::map<double, double> &DepositCalc::GetReplenishmentList()
    const noexcept {
  return replenishments_;
}

const std::map<double, double> &DepositCalc::GetWithdrawalList()
    const noexcept {
  return withdrawals_;
}

}  // namespace s21

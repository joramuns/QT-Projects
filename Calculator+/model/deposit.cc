#include "deposit.h"

namespace s21 {
DepositCalc::DepositCalc() {}

void DepositCalc::AddReplenishment(double day, double amount) {
  replenishments_[day] += amount;
}

void DepositCalc::AddWithdrawal(double day, double amount) {
  withdrawals_[day] += amount;
}

const std::map<double, double> &DepositCalc::GetReplenishmentList() const noexcept {
  return replenishments_;
}

const std::map<double, double> &DepositCalc::GetWithdrawalList() const noexcept {
  return withdrawals_;
}

}  // namespace s21

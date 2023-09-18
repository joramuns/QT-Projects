#ifndef MODEL_DEPOSIT_H_
#define MODEL_DEPOSIT_H_

#include <map>

namespace s21 {
class DepositCalc final {
 public:
  DepositCalc();

  /* Mutators */
  void AddReplenishment(double day, double amount);
  void AddWithdrawal(double day, double amount);

  /* Getters */
  const std::map<double, double> &GetReplenishmentList() const noexcept;
  const std::map<double, double> &GetWithdrawalList() const noexcept;

 private:

 private:
  /* Input data */
  double amount_;
  double term_;
  double interest_rate_;
  int deposit_type_;
  bool capitalization_;
  std::map<double, double> replenishments_;
  std::map<double, double> withdrawals_;
};
}  // namespace s21
#endif  // MODEL_DEPOSIT_H_

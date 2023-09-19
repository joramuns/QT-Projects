#ifndef MODEL_DEPOSIT_H_
#define MODEL_DEPOSIT_H_

#include <map>
#include <vector>

namespace s21 {
class DepositCalc final {
 public:
  DepositCalc();

  /* Mutators */
  void AddReplenishment(double day, double amount) noexcept;
  void RemoveReplenishment(int number) noexcept;
  void AddWithdrawal(double day, double amount) noexcept;
  void RemoveWithdrawal(int number) noexcept;
  void SetDepositData(double amount, int term, double rate) noexcept;
  void SetDepositType(int periodicity, bool capitalization) noexcept;
  void EvaluateDeposit() noexcept;

  /* Getters */
  const std::map<double, double> &GetReplenishmentList() const noexcept;
  const std::map<double, double> &GetWithdrawalList() const noexcept;
  const std::vector<double> &GetPayoffsList() const noexcept;

 private:
 private:
  /* Input data */
  double amount_;
  int term_;
  double interest_rate_;
  int deposit_type_;
  bool capitalization_;
  std::map<double, double> replenishments_;
  std::map<double, double> withdrawals_;
  /* Output data */
  std::vector<double> payoffs_;
  double profit_amount_;
  double end_amount_;
  double tax_amount_;
};
}  // namespace s21
#endif  // MODEL_DEPOSIT_H_

#ifndef MODEL_CREDIT_H_
#define MODEL_CREDIT_H_

#include <cmath>
#include <vector>

namespace s21 {
class CreditCalc final {
 public:
  CreditCalc() noexcept;

  /* Accessors */
  const std::vector<double> GetPayments() const noexcept;
  const double GetOverpayment() const noexcept;
  const double GetTotalPayment() const noexcept;

  /* Mutators */
  void Calculate() noexcept;
  void SetData(double amount, double term, double interest_rate,
               int credit_type) noexcept;

 private:
  void CalculateAnnuity() noexcept;
  void CalculateDifferentiated() noexcept;
  void AnnuityPayment() noexcept;
  void DifferentiatedPayment() noexcept;

 private:
  /* Input data */
  double amount_;
  double term_;
  double interest_rate_;
  int credit_type_;

  /* Output data */
  std::vector<double> payments_;
  double overpayment_;
  double total_payment_;
};
}  // namespace s21
#endif  // MODEL_CREDIT_H_

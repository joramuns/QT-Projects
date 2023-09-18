#ifndef MODEL_CREDIT_H_
#define MODEL_CREDIT_H_

#include <cmath>
#include <vector>

namespace s21 {
class CreditCalc final {
 public:
  CreditCalc();

  /* Modifiers */
  void Calculate();

  /* Mutators */
  void SetData(double amount, double term, double interest_rate,
               int credit_type);

  /* Getters */
  std::vector<double> GetPayments();
  double GetOverpayment();
  double GetTotalPayment();

 private:
  void CalculateAnnuity();
  void CalculateDifferentiated();
  void AnnuityPayment();
  void DifferentiatedPayment();

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

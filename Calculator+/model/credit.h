#ifndef MODEL_CREDIT_H_
#define MODEL_CREDIT_H_

#include <vector>
#include <cmath>

namespace s21 {
class CreditCalc final {
 public:
  CreditCalc() noexcept = default;

  /* Modifiers */
  void CalculateAnnuity();
  void CalculatePayment();

  /* Mutators */
  void SetData(double amount, double term, double interest_rate, bool credit_type);

  /* Getters */
  std::vector<double> GetPayments();
  double GetOverpayment();
  double GetTotalPayment();

 private:
  /* struct InputData { */
  double amount_;
  double term_;
  double interest_rate_;
  bool credit_type_;
  /* }; */
  /* struct OutputData { */
  std::vector<double> payments_;
  double overpayment_;
  double total_payment_;
  /* }; */
  /* InputData input_; */
  /* OutputData output_; */
};
}  // namespace s21
#endif  // MODEL_CREDIT_H_

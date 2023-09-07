#include "credit.h"

namespace s21 {
void CreditCalc::CalculateAnnuity() {
  CalculatePayment();
  total_payment_ = payments_.back() * term_;
  overpayment_ = total_payment_ - amount_;
}

void CreditCalc::CalculatePayment() {
  double payment =
      amount_ *
      (interest_rate_ +
       (interest_rate_ / (std::pow((1.0 + interest_rate_), term_) - 1.0)));
  payments_.push_back(payment);
}

void CreditCalc::SetData(double amount, double term, double interest_rate,
                         bool credit_type) {
  amount_ = amount;
  term_ = term;
  interest_rate_ = interest_rate / (12.0 * 100.0);
  credit_type_ = credit_type;
}

std::vector<double> CreditCalc::GetPayments() { return payments_; }

double CreditCalc::GetOverpayment() { return overpayment_; }

double CreditCalc::GetTotalPayment() { return total_payment_; }
}  // namespace s21

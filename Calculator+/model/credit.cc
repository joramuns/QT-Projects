#include "credit.h"

namespace s21 {

CreditCalc::CreditCalc()
    : amount_(0),
      term_(0),
      interest_rate_(0),
      credit_type_(0),
      overpayment_(0),
      total_payment_(0){};

void CreditCalc::Calculate() {
  payments_.clear();
  total_payment_ = 0;
  if (credit_type_) {
    CalculateDifferentiated();
  } else {
    CalculateAnnuity();
  }
}

void CreditCalc::CalculateAnnuity() {
  AnnuityPayment();
  total_payment_ = payments_.back() * term_;
  overpayment_ = total_payment_ - amount_;
}

void CreditCalc::CalculateDifferentiated() {
  DifferentiatedPayment();
  overpayment_ = total_payment_ - amount_;
}

void CreditCalc::AnnuityPayment() {
  double payment{0};
  if (interest_rate_) {
    payment =
        amount_ *
        (interest_rate_ +
         (interest_rate_ / (std::pow((1.0 + interest_rate_), term_) - 1.0)));
  } else {
    payment = amount_ / term_;
  }
  payment = std::round(payment * 100) / 100;
  payments_.push_back(payment);
}

void CreditCalc::DifferentiatedPayment() {
  double amount = amount_;
  double pay_off = amount_ / term_;

  for (int i = 0; i != term_; ++i) {
    double payment = amount * interest_rate_ + pay_off;
    payment = std::round(payment * 100) / 100;
    payments_.push_back(payment);
    total_payment_ += payment;
    amount -= pay_off;
  }
}

void CreditCalc::SetData(double amount, double term, double interest_rate,
                         int credit_type) {
  amount_ = amount;
  term_ = term;
  interest_rate_ = interest_rate / (12.0 * 100.0);
  credit_type_ = credit_type;
}

std::vector<double> CreditCalc::GetPayments() { return payments_; }

double CreditCalc::GetOverpayment() { return overpayment_; }

double CreditCalc::GetTotalPayment() { return total_payment_; }
}  // namespace s21

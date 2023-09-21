#include "deposit.h"

namespace s21 {
DepositCalc::DepositCalc() noexcept
    : amount_(0.0),
      term_(0),
      interest_rate_(0.0),
      deposit_type_(0),
      tax_rate_(0.0),
      capitalization_(false),
      total_profit_(0.0),
      end_amount_(0.0),
      tax_amount_(0.0) {}

/* Accessors */
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

double DepositCalc::GetTotalProfit() const noexcept { return total_profit_; }

double DepositCalc::GetTaxCharge() const noexcept {
  return total_profit_ * tax_rate_;
}

double DepositCalc::GetEndAmount() const noexcept { return end_amount_; }

/* Mutators */
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

void DepositCalc::SetDepositType(double tax, int periodicity,
                                 bool capitalization) noexcept {
  tax_rate_ = tax;
  deposit_type_ = periodicity;
  capitalization_ = capitalization;
}

void DepositCalc::EvaluateDeposit() noexcept {
  payoffs_.clear();
  double profit_amount = 0.0;
  total_profit_ = 0.0;
  end_amount_ = 0.0;
  tax_amount_ = 0.0;

  int payoffs_number = term_ / deposit_type_;
  if (static_cast<int>(payoffs_.capacity()) < payoffs_number) {
    payoffs_.reserve(payoffs_number);
  }

  double daily_profit = RecalculateDaily();
  for (int day = 1; day <= term_; ++day) {
    if (AccountMovement(day)) {
      daily_profit = RecalculateDaily();
    }
    profit_amount += daily_profit;
    if (day % deposit_type_ == 0 || day == term_) {
      BankRounding(profit_amount);
      payoffs_.push_back(profit_amount);
      total_profit_ += profit_amount;
      if (capitalization_) {
        amount_ += profit_amount;
        end_amount_ = amount_;
        daily_profit = RecalculateDaily();
      } else {
        end_amount_ += profit_amount;
      }
      profit_amount = 0.0;
    }
  }
  end_amount_ = amount_;
}

/* Private deposit model functions */
void DepositCalc::BankRounding(double &number) const noexcept {
  double temp_number = number * 100.0;
  int checker = GetFloatingDigit(number, 3);
  if (checker == 5) {
    checker = GetFloatingDigit(number, 2);
    if (checker % 2 != 0) {
      number = std::ceil(temp_number);
    } else {
      number = std::floor(temp_number);
    }
  } else {
    number = std::round(temp_number);
  }
  number /= 100.0;
}

int DepositCalc::GetFloatingDigit(const double number,
                                  int place) const noexcept {
  int real_number = static_cast<int>(number * std::pow(10.0, place));
  --place;
  int temp_number = static_cast<int>(number * std::pow(10.0, place));
  temp_number *= 10;
  return real_number - temp_number;
}

bool DepositCalc::AccountMovement(const int day) noexcept {
  bool result = false;

  auto wd_iter = withdrawals_.find(static_cast<double>(day));
  if (wd_iter != withdrawals_.end()) {
    result = true;
    if (amount_ > wd_iter->second) {
      amount_ -= wd_iter->second;
    } else {
      withdrawals_.erase(wd_iter);
    }
  }
  auto rep_iter = replenishments_.find(static_cast<double>(day));
  if (rep_iter != replenishments_.end()) {
    result = true;
    amount_ += rep_iter->second;
  }

  return result;
}
double DepositCalc::RecalculateDaily() const noexcept {
  return (amount_ * interest_rate_) / 365.0;
}

}  // namespace s21

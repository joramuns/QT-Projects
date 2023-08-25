#include "infix.h"

namespace s21 {
void InfixExpr::AddElement(const Element &token) noexcept {
  infix_data_.push_back(token);
};

void InfixExpr::DelElement() noexcept { infix_data_.pop_back(); }

int InfixExpr::ValidateExpr() const noexcept {
  int result = 0;
  return result;
}

void InfixExpr::ClearInfixExpr() noexcept { infix_data_.clear(); }

void InfixExpr::AppendNumber(const double number) noexcept { infix_data_.back().AppendNumber(number); }

std::deque<Element> InfixExpr::GetInfixData() const noexcept { return infix_data_; }

std::string InfixExpr::GetInfixString() const noexcept {
  std::string result{};
  for (const auto &item : infix_data_) {
    result += *item + " ";
  }
  return result;
}

bool InfixExpr::LastIsOperator() const noexcept {
  /* return true; */
  return infix_data_.empty() ? true : infix_data_.back().IsOperator();
}
}  // namespace s21

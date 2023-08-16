#include "infix.h"

namespace s21 {
void InfixExpr::AddElement(const Element &token) noexcept {
  data_.push_back(token);
};

void InfixExpr::DelElement() noexcept { data_.pop_back(); }

std::deque<Element> InfixExpr::GetInfixData() const noexcept { return data_; }
}  // namespace s21

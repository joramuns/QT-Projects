#include "element.h"

namespace s21 {
Element::Element(int input) noexcept
    : is_operand_(true), value_((double)input) {}

Element::Element(double input) noexcept : is_operand_(false), value_(input) {}

/* Getters */
bool Element::GetType() const noexcept { return is_operand_; }

double Element::GetValue() const noexcept { return value_; }

int Element::GetPriority() const noexcept {
  return is_operand_ ? (int)log10(value_) : -1;
}

/* Modifiers */
bool Element::AppendNumber(double input) noexcept {
  if (GetType()) {
    return false;
  } else {
    value_ *= 10;
    value_ += input;
    return true;
  }
}
}  // namespace s21

#include "element.h"

namespace s21 {
Element::Element(int input) noexcept
    : is_operator_(true), value_((double)input) {}

Element::Element(double input) noexcept : is_operator_(false), value_(input) {}

/* Getters */
bool Element::IsOperator() const noexcept { return is_operator_; }

double Element::GetValue() const noexcept { return value_; }

int Element::GetPriority() const noexcept {
  return is_operator_ ? (int)log10(value_) : -1;
}

/* Modifiers */
bool Element::AppendNumber(double input) noexcept {
  if (IsOperator()) {
    return false;
  } else {
    value_ *= 10;
    value_ += input;
    return true;
  }
}

bool Element::AppendNumber(double input, int power) noexcept {
  if (IsOperator()) {
    return false;
  } else {
    while (power--) {
      input /= 10;
    }
    value_ += input;
    return true;
  }
}
}  // namespace s21

std::ostream &operator<<(std::ostream &os, const s21::Element &output) {
  double value = output.GetValue();
  if (output.IsOperator()) {
    if (value == s21::Element::kAddition) {
      os << "+";
    } else if (value == s21::Element::kSubtraction) {
      os << "-";
    } else if (value == s21::Element::kModulus) {
      os << "mod";
    } else if (value == s21::Element::kMultiplication) {
      os << "*";
    } else if (value == s21::Element::kDivision) {
      os << "/";
    } else if (value == s21::Element::kSin) {
      os << "sin";
    } else if (value == s21::Element::kCos) {
      os << "cos";
    } else if (value == s21::Element::kTan) {
      os << "tan";
    } else if (value == s21::Element::kAsin) {
      os << "asin";
    } else if (value == s21::Element::kAcos) {
      os << "acos";
    } else if (value == s21::Element::kAtan) {
      os << "atan";
    } else if (value == s21::Element::kSqrt) {
      os << "sqrt";
    } else if (value == s21::Element::kLn) {
      os << "ln";
    } else if (value == s21::Element::kLog) {
      os << "log";
    } else if (value == s21::Element::kPower) {
      os << "^";
    } else if (value == s21::Element::kBracketOpen) {
      os << "(";
    } else if (value == s21::Element::kBracketClose) {
      os << ")";
    }
  } else {
    os << value;
  }

  return os;
}

#include "element.h"

namespace s21 {
Element::Element(const int input) noexcept
    : is_operator_(true), value_((double)input) {}

Element::Element(const double input) noexcept : is_operator_(false), value_(input) {}

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
/* Overload operator methods */
Element Element::operator+(const Element &other) const noexcept {
  return Element(GetValue() + other.GetValue());
}

Element Element::operator-(const Element &other) const noexcept {
  return Element(GetValue() - other.GetValue());
}

Element Element::operator%(const Element &other) const noexcept {
  return Element(std::fmod(GetValue(), other.GetValue()));
}

Element Element::operator*(const Element &other) const noexcept {
  return Element(GetValue() * other.GetValue());
}

Element Element::operator/(const Element &other) const noexcept {
  return Element(GetValue() / other.GetValue());
}

Element Element::operator^(const Element &other) const noexcept {
  return Element(std::pow(GetValue(), other.GetValue()));
}

std::string Element::operator*() const noexcept {
  double value = GetValue();
  std::string result{};
  if (IsOperator()) {
    if (value == s21::Element::kAddition) {
      result = "+";
    } else if (value == s21::Element::kSubtraction) {
      result = "-";
    } else if (value == s21::Element::kModulus) {
      result = "mod";
    } else if (value == s21::Element::kMultiplication) {
      result = "*";
    } else if (value == s21::Element::kDivision) {
      result = "/";
    } else if (value == s21::Element::kSin) {
      result = "sin";
    } else if (value == s21::Element::kCos) {
      result = "cos";
    } else if (value == s21::Element::kTan) {
      result = "tan";
    } else if (value == s21::Element::kAsin) {
      result = "asin";
    } else if (value == s21::Element::kAcos) {
      result = "acos";
    } else if (value == s21::Element::kAtan) {
      result = "atan";
    } else if (value == s21::Element::kSqrt) {
      result = "sqrt";
    } else if (value == s21::Element::kLn) {
      result = "ln";
    } else if (value == s21::Element::kLog) {
      result = "log";
    } else if (value == s21::Element::kPower) {
      result = "^";
    } else if (value == s21::Element::kBracketOpen) {
      result = "(";
    } else if (value == s21::Element::kBracketClose) {
      result = ")";
    }
  } else {
    /* std::setlocale(LC_ALL, "C"); */
    std::ostringstream num_to_string;
    /* num_to_string << std::fixed; */
    num_to_string << value;
    result = num_to_string.str();
  }

  return result;
}

/* Unary operation methods */
Element Element::sin() const noexcept { return Element(std::sin(GetValue())); }

Element Element::cos() const noexcept { return Element(std::cos(GetValue())); }

Element Element::tan() const noexcept { return Element(std::tan(GetValue())); }

Element Element::asin() const noexcept {
  return Element(std::asin(GetValue()));
}

Element Element::acos() const noexcept {
  return Element(std::acos(GetValue()));
}

Element Element::atan() const noexcept {
  return Element(std::atan(GetValue()));
}

Element Element::sqrt() const noexcept {
  return Element(std::sqrt(GetValue()));
}

Element Element::ln() const noexcept { return Element(std::log(GetValue())); }

Element Element::log() const noexcept {
  return Element(std::log10(GetValue()));
}

}  // namespace s21

std::ostream &operator<<(std::ostream &os, const s21::Element &output) {
  return os << *output;
}

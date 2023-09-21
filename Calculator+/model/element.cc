#include "element.h"

namespace s21 {
Element::Element() noexcept : is_operator_(false), value_(0){};

Element::Element(const int input) noexcept
    : is_operator_(true), value_((double)input) {}

Element::Element(const double input) noexcept
    : is_operator_(false), value_(input) {}

Element::Element(const char input) noexcept : is_operator_(false), value_(0) {
  string_value_ += input;
  if (input != 'x') {
    if (string_value_ == "." || string_value_ == "e") {
      string_value_ = "0" + string_value_;
    }
    value_ = std::stod(string_value_);
  }
}

/* Getters */
const bool Element::IsOperator() const noexcept { return is_operator_; }

const bool Element::IsVariable() const noexcept { return string_value_ == "x"; }

const double Element::GetValue() const noexcept { return value_; }

const int Element::GetPriority() const noexcept {
  return is_operator_ ? (int)log10(value_) : -1;
}

/* Modifiers */
void Element::AppendNumber(const char input) noexcept {
  bool allowed = true;
  char last_char = string_value_.back();

  if (input == 'e') {
    allowed = CheckE(last_char);
  } else if (input == '.') {
    allowed = CheckDot();
  } else {
    allowed = CheckDigit();
  }
  if (allowed) {
    string_value_ += input;
    value_ = std::stod(string_value_);
  }
}

void Element::SetUnary() noexcept {
  if (value_ == Element::OperatorType::kAddition) {
    value_ = Element::OperatorType::kUnaryAddition;
  } else if (value_ == Element::OperatorType::kSubtraction) {
    value_ = Element::OperatorType::kUnarySubtraction;
  }
}

void Element::SetValue(const double number) noexcept { value_ = number; }

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
    if (value == s21::Element::kAddition ||
        value == s21::Element::kUnaryAddition) {
      result = "\u002B";
    } else if (value == s21::Element::kSubtraction ||
               value == s21::Element::kUnarySubtraction) {
      result = "\u2212";
    } else if (value == s21::Element::kModulus) {
      result = "mod";
    } else if (value == s21::Element::kMultiplication) {
      result = "\u00D7";
    } else if (value == s21::Element::kDivision) {
      result = "\u00F7";
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
    result = string_value_;
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

/* Private element functions */
bool Element::CheckE(const char last_char) noexcept {
  bool allowed = true;

  if (string_value_.find('e') != std::string::npos) {
    allowed = false;
    if (last_char == 'e') {
      string_value_ += '+';
    } else if (last_char == '+' || last_char == '-') {
      string_value_.back() = last_char == '+' ? '-' : '+';
    }
  } else if (last_char == '.') {
    string_value_ += '0';
  }

  return allowed;
}

bool Element::CheckDot() noexcept {
  bool allowed = true;

  if (string_value_.find('e') != std::string::npos ||
      string_value_.find('.') != std::string::npos) {
    allowed = false;
  }

  return allowed;
}

bool Element::CheckDigit() noexcept {
  bool allowed = true;
  auto e_place = string_value_.find('e');

  if (string_value_.find('+') != std::string::npos ||
      string_value_.find('-') != std::string::npos) {
    ++e_place;
  }
  if (e_place != std::string::npos) {
    auto count_chars_after_e = string_value_.size() - e_place;
    if (count_chars_after_e > 2) {
      allowed = false;
    }
  }

  return allowed;
}

}  // namespace s21

std::ostream &operator<<(std::ostream &os, const s21::Element &output) {
  return os << *output;
}

#ifndef MODEL_ELEMENT_H_
#define MODEL_ELEMENT_H_

#include <cmath>
#include <iostream>
#include <sstream>

namespace s21 {
class Element final {
 public:
  /* RFive */
  Element() noexcept;
  explicit Element(const int input) noexcept;
  explicit Element(const double input) noexcept;
  explicit Element(const char input) noexcept;

  /* Getters */
  [[nodiscard]] const bool IsOperator() const noexcept;
  [[nodiscard]] const bool IsVariable() const noexcept;
  [[nodiscard]] const double GetValue() const noexcept;
  [[nodiscard]] const int GetPriority() const noexcept;

  /* Modifiers */
  void AppendNumber(const char input) noexcept;
  void SetUnary() noexcept;
  void SetValue(const double number) noexcept;

  /* Overload operator methods */
  Element operator+(const Element &other) const noexcept;
  Element operator-(const Element &other) const noexcept;
  Element operator%(const Element &other) const noexcept;
  Element operator*(const Element &other) const noexcept;
  Element operator/(const Element &other) const noexcept;
  Element operator^(const Element &other) const noexcept;
  std::string operator*() const noexcept;

  /* Unary operation methods */
  Element sin() const noexcept;
  Element cos() const noexcept;
  Element tan() const noexcept;
  Element asin() const noexcept;
  Element acos() const noexcept;
  Element atan() const noexcept;
  Element sqrt() const noexcept;
  Element ln() const noexcept;
  Element log() const noexcept;

 public:
  /* Priority is shown by rang of 10 power */
  enum OperatorType {
    kAddition = 1,
    kSubtraction,
    kUnaryAddition,
    kUnarySubtraction,
    kMultiplication = 10,
    kDivision,
    kModulus,
    kPower,
    kSin = 1000,
    kCos,
    kTan,
    kAsin,
    kAcos,
    kAtan,
    kSqrt,
    kLn,
    kLog,
    kBracketOpen = 10000,
    kBracketClose
  };

  enum PriorityType {
    kSubAdd = 0,
    kMulDivModPow,
    kTrigonometry = 3,
    kBrackets
  };

 private:
  bool CheckE(const char last_char) noexcept;
  bool CheckDot() noexcept;
  bool CheckDigit() noexcept;

 private:
  bool is_operator_;
  double value_;
  std::string string_value_{};
};
}  // namespace s21

std::ostream &operator<<(std::ostream &os, const s21::Element &output);

#endif  // MODEL_ELEMENT_H_

#ifndef MODEL_ELEMENT_H_
#define MODEL_ELEMENT_H_

#include <cmath>
#include <iostream>

namespace s21 {
class Element final {
 public:
  /* RFive */
  Element() = default;
  explicit Element(int input) noexcept;
  explicit Element(double input) noexcept;
  Element(const Element &other) = default;
  Element(Element &&other) = default;
  Element &operator=(const Element &other) = delete;
  Element &operator=(Element &&other) = default;
  ~Element() = default;

  /* Getters */
  bool IsOperator() const noexcept;
  double GetValue() const noexcept;
  int GetPriority() const noexcept;

  /* Modifiers */
  bool AppendNumber(double input) noexcept;
  bool AppendNumber(double input, int power) noexcept;

  /* Overload operator methods */
  Element operator+(const Element &other) const noexcept;
  Element operator-(const Element &other) const noexcept;
  Element operator%(const Element &other) const noexcept;
  Element operator*(const Element &other) const noexcept;
  Element operator/(const Element &other) const noexcept;
  Element operator^(const Element &other) const noexcept;

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

 private:
  bool is_operator_;
  double value_;
};
}  // namespace s21

std::ostream &operator<<(std::ostream &os, const s21::Element &output);

#endif  // MODEL_ELEMENT_H_

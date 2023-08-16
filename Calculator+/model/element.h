#ifndef MODEL_ELEMENT_H_
#define MODEL_ELEMENT_H_

#include <cmath>
#include <iostream>

namespace s21 {
class Element final {
 public:
  /* RFive */
  Element() = delete;
  explicit Element(int input) noexcept;
  explicit Element(double input) noexcept;
  Element(const Element &other) = default;
  Element(Element &&other) = delete;
  Element &operator=(const Element &other) = delete;
  Element &operator=(Element &&other) = delete;
  ~Element() = default;

  /* Getters */
  bool GetType() const noexcept;
  double GetValue() const noexcept;
  int GetPriority() const noexcept;

  /* Modifiers */
  bool AppendNumber(double input) noexcept;
  bool AppendNumber(double input, int power) noexcept;

 public:
  /* Priority is shown by rang of 10 power */
  enum {
    kAddition = 1,
    kSubtraction,
    kModulus,
    kMultiplication = 10,
    kDivision,
    kSin = 100,
    kCos,
    kTan,
    kAsin,
    kAcos,
    kAtan,
    kSqrt,
    kLn,
    kLog,
    kPower = 1000,
    kBracketOpen = 10000,
    kBracketClose 
  };

 private:
  bool is_operand_;
  double value_;
};
}  // namespace s21

std::ostream &operator<<(std::ostream &os, const s21::Element &output);

#endif  // MODEL_ELEMENT_H_

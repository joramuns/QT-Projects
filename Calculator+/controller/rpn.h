#ifndef CONTROLLER_RPN_H_
#define CONTROLLER_RPN_H_

#include <queue>
#include <stack>

#include "element.h"

namespace s21 {
class Converter {
 public:
  /* RFive */
  Converter() = default;
  Converter(const Converter &other) = delete;
  Converter(Converter &&other) = delete;
  Converter &operator=(const Converter &other) = delete;
  Converter &operator=(Converter &&other) = delete;
  ~Converter() = default;

  /* methods */
  void AddOperand(Element number);
  void AddOperator(Element operand);

 private:
  /* fields */
  std::queue<Element> stack_out_;
  std::queue<Element> queue_stack_;
};
}  // namespace s21
#endif  // CONTROLLER_RPN_H_

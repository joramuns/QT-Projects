#ifndef CONTROLLER_RPN_H_
#define CONTROLLER_RPN_H_

#include <deque>
#include <iostream>

#include "element.h"

namespace s21 {
class Converter final {
 public:
  /* RFive */
  Converter() = default;
  Converter(const Converter &other) = delete;
  Converter(Converter &&other) = delete;
  Converter &operator=(const Converter &other) = delete;
  Converter &operator=(Converter &&other) = delete;
  ~Converter() = default;

  /* Modifiers */
  void AddOperand(Element number);
  void AddOperator(Element operation);
  void Finalize();

  /* Getters */
  bool IsBroken() const noexcept;

  /* Debug getters */
  std::deque<Element> GetStack() const noexcept;
  std::deque<Element> GetQueue() const noexcept;

 private:
  /* Fields */
  std::deque<Element> stack_out_;
  std::deque<Element> queue_stack_;
  bool is_broken_ = false;

 private:
  void FinalizeBrackets();
  void Pour();
};
}  // namespace s21

std::ostream &operator<<(std::ostream &stream, const s21::Converter &output);
#endif  // CONTROLLER_RPN_H_

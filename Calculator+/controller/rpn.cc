#include "rpn.h"

namespace s21 {
/* Modifiers */
void Converter::AddOperand(Element number) { stack_out_.push_back(number); }

/* Getters */
bool Converter::IsBroken() const noexcept { return is_broken_; }

/* Debug getters */
std::deque<Element> Converter::GetStack() const noexcept { return stack_out_; }

std::deque<Element> Converter::GetQueue() const noexcept {
  return queue_stack_;
}
}  // namespace s21

std::ostream &operator<<(std::ostream &os, const s21::Converter &output) {
  for (const auto &item : output.GetStack()) {
    os << item << " ";
  }
  os << std::endl;
  for (const auto &item : output.GetQueue()) {
    os << item << " ";
  }
  if (output.IsBroken()) os << std::endl << "Stack is broken!";
  /* os << "Queue stack: " << output.GetQueue() << std::endl; */
  /* os << "Ready stack: " << output.GetStack() << std::endl; */

  return os;
}

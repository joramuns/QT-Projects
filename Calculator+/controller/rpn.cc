#include "rpn.h"

namespace s21 {
/* Modifiers */
void Converter::AddOperand(Element number) { stack_out_.push_back(number); }

void Converter::AddOperator(Element operation) {
  if (queue_stack_.empty()) {
    queue_stack_.push_back(operation);
  } else {
    int operation_priority = operation.GetPriority();
    int operation_type = (int)operation.GetValue();
    int out_priority = queue_stack_.back().GetPriority();
    if (operation_type == s21::Element::kBracketOpen) {
      queue_stack_.push_back(operation);
    } else if (operation_type == s21::Element::kBracketClose) {
      FinalizeBrackets();
      if (!queue_stack_.empty()) {
        queue_stack_.pop_back();
      }
    } else if (operation_priority > out_priority ||
               (operation_type == s21::Element::kPower &&
                operation_priority == out_priority)) {
      queue_stack_.push_back(operation);
    } else if (operation_priority == out_priority) {
      stack_out_.push_back(queue_stack_.back());
      queue_stack_.pop_back();
      queue_stack_.push_back(operation);
    } else {
      if ((int)queue_stack_.back().GetValue() != s21::Element::kBracketOpen) {
        Finalize();
      }
      queue_stack_.push_back(operation);
    }
  }
}

void Converter::Finalize() {
  while (!queue_stack_.empty()) {
    Pour();
  }
}

void Converter::FinalizeBrackets() {
  while (!queue_stack_.empty() &&
         queue_stack_.back().GetValue() != s21::Element::kBracketOpen) {
    Pour();
  }
}

void Converter::Pour() {
  stack_out_.push_back(queue_stack_.back());
  queue_stack_.pop_back();
}

/* Getters */
bool Converter::IsBroken() const noexcept { return is_broken_; }

/* Debug getters */
std::deque<Element> Converter::GetStack() const noexcept { return stack_out_; }

std::deque<Element> Converter::GetQueue() const noexcept {
  return queue_stack_;
}
}  // namespace s21

std::ostream &operator<<(std::ostream &os, const s21::Converter &output) {
  os << "Ready stack: ";
  for (const auto &item : output.GetStack()) {
    os << item << " ";
  }
  os << std::endl << "Queue stack: ";
  for (const auto &item : output.GetQueue()) {
    os << item << " ";
  }
  if (output.IsBroken()) os << std::endl << "Stack is broken!";
  return os;
}

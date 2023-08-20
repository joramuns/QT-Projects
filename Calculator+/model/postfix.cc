#include "postfix.h"

namespace s21 {
/* Modifiers */
void PostfixExpr::AddOperand(Element number) noexcept {
  stack_out_.push_back(number);
}

void PostfixExpr::AddOperator(Element operation) noexcept {
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
        if (!queue_stack_.empty() && queue_stack_.back().GetPriority() == 2) {
          Pour();
        }
      }
    } else if (operation_priority > out_priority) {
      queue_stack_.push_back(operation);
    } else if (operation_priority == out_priority) {
      stack_out_.push_back(queue_stack_.back());
      queue_stack_.pop_back();
      queue_stack_.push_back(operation);
    } else {
      if (!queue_stack_.empty() && queue_stack_.back().GetPriority() == 3) {
        Pour();
      } else {
        PourAll();
      }
      queue_stack_.push_back(operation);
    }
  }
}

void PostfixExpr::PourAll() noexcept {
  while (!queue_stack_.empty() &&
         (int)queue_stack_.back().GetValue() != s21::Element::kBracketOpen) {
    Pour();
  }
}

void PostfixExpr::ClearPostfixExpr() noexcept { stack_out_.clear(); }

/* Getters */
bool PostfixExpr::IsBroken() const noexcept { return is_broken_; }

/* Debug getters */
std::deque<Element> PostfixExpr::GetPostfixExpr() const noexcept {
  return stack_out_;
}

std::deque<Element> PostfixExpr::GetQueue() const noexcept {
  return queue_stack_;
}

/* Private functions */
void PostfixExpr::FinalizeBrackets() {
  while (!queue_stack_.empty() &&
         queue_stack_.back().GetValue() != s21::Element::kBracketOpen) {
    Pour();
  }
}

void PostfixExpr::Pour() {
  stack_out_.push_back(queue_stack_.back());
  queue_stack_.pop_back();
}
}  // namespace s21

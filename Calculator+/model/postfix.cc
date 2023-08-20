#include "postfix.h"

namespace s21 {
/* Getters */

/* Modifiers */
void PostfixExpr::AddOperand(const Element &number) noexcept {
  stack_out_.push_back(number);
}

void PostfixExpr::AddOperator(const Element &operation) noexcept {
  int operation_type = (int)operation.GetValue();
  if (queue_stack_.empty()) {
    queue_stack_.push_back(operation);
  } else if (operation_type == OpType::kBracketClose) {
    PourAll();
    queue_stack_.pop_back();
    if (!queue_stack_.empty() && queue_stack_.back().GetPriority() == 3) {
      Pour();
    }
  } else {
    int queue_priority = queue_stack_.back().GetPriority();
    int operation_priority = operation.GetPriority();
    if (operation_priority == queue_priority &&
        operation_type != OpType::kPower) {
      Pour();
    } else if (operation_priority < queue_priority) {
      PourAll();
    }
    queue_stack_.push_back(operation);
  }
}

void PostfixExpr::ClearPostfixExpr() noexcept { stack_out_.clear(); }

void PostfixExpr::PourAll() noexcept {
  while (!queue_stack_.empty() && !TopOpenBracket()) {
    Pour();
  }
}

/* Debug getters */
std::deque<Element> PostfixExpr::GetPostfixExpr() const noexcept {
  return stack_out_;
}

std::deque<Element> PostfixExpr::GetQueue() const noexcept {
  return queue_stack_;
}

/* Private functions */
void PostfixExpr::Pour() noexcept {
  stack_out_.push_back(queue_stack_.back());
  queue_stack_.pop_back();
}

bool PostfixExpr::TopOpenBracket() const noexcept {
  return (int)queue_stack_.back().GetValue() == OpType::kBracketOpen;
}
}  // namespace s21

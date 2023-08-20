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
    int queue_priority = queue_stack_.back().GetPriority();
    int queue_type = (int)queue_stack_.back().GetValue();
    /* Handle open bracket - push to queue */
    if (operation_type == OpType::kBracketOpen) {
      queue_stack_.push_back(operation);
      /* Handle close bracket - pop everything out from queue until open
       * bracket, then discard brackets */
    } else if (operation_type == OpType::kBracketClose) {
      PourAll();
      queue_stack_.pop_back();
      /* Pour unary operation */
      if (queue_priority == 3) {
        Pour();
      }
      /* Handle greater priority operator - push it, or if there is a power
       * operator in queue and current operator is power - do the same due to
       * right associativity */
    } else if (operation_priority > queue_priority ||
               (operation_priority == queue_priority && queue_type == OpType::kPower)) {
      queue_stack_.push_back(operation);
      /* In case of equality of current and last queue operators or there is a
       * power operator on top and current is multiply or division (priority 1)
       * - pop from queue and push it to output, push current to queue. */
    } else if (operation_priority == queue_priority ||
               (operation_priority == 1 && queue_type == OpType::kPower)) {
      Pour();
      queue_stack_.push_back(operation);
      /* Case when current operator priority is lesser than operator in queue -
       * pour all from queue. */
    } else {
      PourAll();
      queue_stack_.push_back(operation);
    }
  }
}

void PostfixExpr::ClearPostfixExpr() noexcept { stack_out_.clear(); }

void PostfixExpr::PourAll() noexcept {
  while (!queue_stack_.empty() &&
         (int)queue_stack_.back().GetValue() != OpType::kBracketOpen) {
    Pour();
  }
}

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
void PostfixExpr::Pour() noexcept {
  stack_out_.push_back(queue_stack_.back());
  queue_stack_.pop_back();
}

bool PostfixExpr::IsPower() const noexcept {
  return (int)queue_stack_.back().GetValue() == OpType::kPower;
}
}  // namespace s21

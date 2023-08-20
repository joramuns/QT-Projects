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
    /* Handle open bracket - push to queue */
    if (operation_type == s21::Element::kBracketOpen) {
      queue_stack_.push_back(operation);
      /* Handle close bracket - pop everything out from queue until open
       * bracket, then discard brackets */
    } else if (operation_type == s21::Element::kBracketClose) {
      FinalizeBrackets();
      if (!queue_stack_.empty()) {
        queue_stack_.pop_back();
        /* Pour unary operation */
        if (!queue_stack_.empty() && out_priority == 2) {
          Pour();
        }
      }
      /* Handle greater priority operator - push it, or if there is a power
       * operator in queue and current operator is power - do the same */
    } else if (operation_priority > out_priority ||
               (operation_priority == out_priority && out_priority == 3)) {
      queue_stack_.push_back(operation);
      /* In case of equality of current and last queue operators - pop from
       * queue and push it to output, push current to queue */
    } else if (operation_priority == out_priority) {
      stack_out_.push_back(queue_stack_.back());
      queue_stack_.pop_back();
      queue_stack_.push_back(operation);
      /* Case when current operator priority is lesser than operator in queue.
       * If there is power operation in queue - pop it, otherwise - pop all */
    } else {
      if (!queue_stack_.empty() && out_priority == 3) {
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

#ifndef MODEL_POSTFIX_H_
#define MODEL_POSTFIX_H_

#include <deque>
#include <iostream>

#include "element.h"

namespace s21 {
class PostfixExpr {
 public:
  PostfixExpr() = default;

 protected:
  using OpType = s21::Element::OperatorType;
  /* Modifiers */
  void AddOperand(const Element &number) noexcept;
  void AddOperator(const Element &operation) noexcept;
  void ClearPostfixExpr() noexcept;
  void PopAndPushAll() noexcept;

  /* Accessors */
  [[nodiscard]] const std::deque<Element> &GetPostfixExpr() const noexcept;

  /* Debug accessor */
  /* [[nodiscard]] const std::deque<Element> &GetQueue() const noexcept; */

 private:
  void PopAndPush() noexcept;
  [[nodiscard]] bool TopOpenBracket() const noexcept;

 private:
  /* Fields */
  std::deque<Element> stack_out_;
  std::deque<Element> queue_stack_;
};

}  // namespace s21

#endif  // MODEL_POSTFIX_H_

#ifndef MODEL_POSTFIX_H_
#define MODEL_POSTFIX_H_

#include <deque>
#include <iostream>

#include "element.h"

namespace s21 {
class PostfixExpr {
 public:
  /* RFive */
  PostfixExpr() = default;
  PostfixExpr(const PostfixExpr &other) = delete;
  PostfixExpr(PostfixExpr &&other) = delete;
  PostfixExpr &operator=(const PostfixExpr &other) = delete;
  PostfixExpr &operator=(PostfixExpr &&other) = delete;
  virtual ~PostfixExpr() = default;

  /* Getters */

 protected:
  using OpType = s21::Element::OperatorType;
  /* Modifiers */
  void AddOperand(const Element &number) noexcept;
  void AddOperator(const Element &operation) noexcept;
  void ClearPostfixExpr() noexcept;
  void PopAndPushAll() noexcept;

  /* Debug getters */
  std::deque<Element> GetPostfixExpr() const noexcept;
  std::deque<Element> GetQueue() const noexcept;

 private:
  /* Fields */
  std::deque<Element> stack_out_;
  std::deque<Element> queue_stack_;

 private:
  void PopAndPush() noexcept;
  bool TopOpenBracket() const noexcept;
};
}  // namespace s21

#endif  // MODEL_POSTFIX_H_

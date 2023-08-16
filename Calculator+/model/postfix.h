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
  bool IsBroken() const noexcept;

  /* Debug getters */
  std::deque<Element> GetStack() const noexcept;
  std::deque<Element> GetQueue() const noexcept;

 protected:
  /* Modifiers */
  void AddOperand(Element number) noexcept;
  void AddOperator(Element operation) noexcept;
  void Finalize() noexcept;

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

#endif  // MODEL_POSTFIX_H_

#ifndef MODEL_POSTFIX_H_
#define MODEL_POSTFIX_H_

#include <deque>
#include <iostream>

#include "element.h"

namespace s21 {
class PostfixExpr final {
 public:
  /* RFive */
  PostfixExpr() = default;
  PostfixExpr(const PostfixExpr &other) = delete;
  PostfixExpr(PostfixExpr &&other) = delete;
  PostfixExpr &operator=(const PostfixExpr &other) = delete;
  PostfixExpr &operator=(PostfixExpr &&other) = delete;
  ~PostfixExpr() = default;

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

std::ostream &operator<<(std::ostream &stream, const s21::PostfixExpr &output);
#endif  // MODEL_POSTFIX_H_

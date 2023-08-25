#ifndef MODEL_INFIX_H_
#define MODEL_INFIX_H_

#include <deque>

#include "element.h"

namespace s21 {
class InfixExpr {
 public:
  /* RFive */
  InfixExpr() = default;
  InfixExpr(const InfixExpr &other) = default;
  InfixExpr(InfixExpr &&other) = delete;
  InfixExpr &operator=(const InfixExpr &other) = default;
  InfixExpr &operator=(InfixExpr &&other) = delete;
  virtual ~InfixExpr() = default;

  /* Modifiers */
  void AddElement(const char number) noexcept;
  void AddElement(const Element &token) noexcept;
  void DelElement() noexcept;
  int ValidateExpr() const noexcept;
  void ClearInfixExpr() noexcept;
  void AppendNumber(const char number) noexcept;

  /* Getters */
  std::deque<Element> GetInfixData() const noexcept;
  std::string GetInfixString() const noexcept;
  bool LastIsOperator() const noexcept;

 private:
  std::deque<Element> infix_data_;
};
}  // namespace s21

#endif  // MODEL_INFIX_H_

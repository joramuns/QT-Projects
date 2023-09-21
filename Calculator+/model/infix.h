#ifndef MODEL_INFIX_H_
#define MODEL_INFIX_H_

#include <deque>
#include <memory>
#include <vector>

#include "element.h"

namespace s21 {
class InfixExpr {
  using elem_iterator = std::deque<std::unique_ptr<Element>>::iterator;

 public:
  /* RFive */
  InfixExpr() = default;
  InfixExpr(const InfixExpr &other) = default;
  InfixExpr(InfixExpr &&other) = delete;
  InfixExpr &operator=(const InfixExpr &other) = default;
  InfixExpr &operator=(InfixExpr &&other) = delete;
  virtual ~InfixExpr() = default;

  /* Modifiers */
  void AddElement(const int type);
  void AddElement(const char number);
  void AddElement(std::unique_ptr<Element> token) noexcept;
  void DelElement() noexcept;
  int ValidateExpr() noexcept;
  void ClearInfixExpr() noexcept;
  void AppendNumber(const char number) noexcept;
  void SetVariables(const double number) noexcept;

  /* Getters */
  const std::deque<std::unique_ptr<Element>> &GetInfixData() const noexcept;
  std::string GetInfixString() const noexcept;
  bool LastIsOperator() const noexcept;
  bool LastIsVariable() const noexcept;

 private:
  int SizeValid(const elem_iterator iter_begin);
  int BeginValid(const elem_iterator iter_begin);
  int EndValid();
  int MiddleValid(elem_iterator iter_begin);
  int DoubleOperator(const elem_iterator type_first,
                     const elem_iterator type_second);

 private:
  std::deque<std::unique_ptr<Element>> infix_data_;
  std::vector<Element *> var_array_;
};
}  // namespace s21

#endif  // MODEL_INFIX_H_

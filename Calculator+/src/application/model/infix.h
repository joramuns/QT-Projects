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
  InfixExpr() = default;

 public:
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
  [[nodiscard]] const std::deque<std::unique_ptr<Element>> &GetInfixData()
      const noexcept;
  [[nodiscard]] const std::string GetInfixString() const noexcept;
  [[nodiscard]] bool LastIsOperator() const noexcept;
  [[nodiscard]] bool LastIsVariable() const noexcept;

 private:
  [[nodiscard]] int SizeValid(const elem_iterator iter_begin) const noexcept;
  [[nodiscard]] int BeginValid(const elem_iterator iter_begin) const noexcept;
  [[nodiscard]] int EndValid() const noexcept;
  [[nodiscard]] int MiddleValid(elem_iterator iter_begin) const noexcept;
  [[nodiscard]] int DoubleOperator(
      const elem_iterator type_first,
      const elem_iterator type_second) const noexcept;

 private:
  std::deque<std::unique_ptr<Element>> infix_data_;
  std::vector<Element *> var_array_;
};
}  // namespace s21

#endif  // MODEL_INFIX_H_

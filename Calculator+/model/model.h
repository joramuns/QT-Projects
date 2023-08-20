#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <stack>

#include "infix.h"
#include "postfix.h"

namespace s21 {
class Model final : public InfixExpr, public PostfixExpr {
 public:
  Model() = default;
  Model(const Model &other) = delete;
  Model(Model &&other) = delete;
  Model &operator=(const Model &other) = delete;
  Model &operator=(Model &&other) = delete;

  /* Modifiers */
  void Convert() noexcept;
  void ClearModel() noexcept;

  /* Calculators */
  double Evaluate() noexcept;

  /* Debug output */
  void OutputModel() noexcept;

 private:
  Element Calculate(const Element &a, const Element &b,
                    OpType math_operator) const noexcept;
  /* Overload for unary operators */
  Element Calculate(const Element &a, OpType math_operator) const noexcept;
};
}  // namespace s21
#endif  // MODEL_MODEL_H_

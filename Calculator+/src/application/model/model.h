#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <stack>

#include "credit.h"
#include "deposit.h"
#include "infix.h"
#include "postfix.h"

namespace s21 {
class Model final : public InfixExpr, public PostfixExpr {
 public:
  Model() = default;

  /* Mutators */
  void Convert() noexcept;
  void ClearModel() noexcept;

  /* Calculators */
  [[nodiscard]] double Evaluate() noexcept;
  [[nodiscard]] const std::string GetResult() noexcept;
  [[nodiscard]] const std::pair<std::vector<double>, std::vector<double>>
  GetCoordinates(const std::vector<double> &value_borders);

  /* Debug output */
  /* void OutputModel() noexcept; */

 public:
  CreditCalc credit_model_;
  DepositCalc deposit_model_;

 private:
  [[nodiscard]] const Element Calculate(const Element &a, const Element &b,
                                        OpType math_operator) const noexcept;
  /* Overload for unary operators */
  [[nodiscard]] const Element Calculate(const Element &a,
                                        OpType math_operator) const noexcept;
};

}  // namespace s21
#endif  // MODEL_MODEL_H_

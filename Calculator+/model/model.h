#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

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
  void Convert();

  /* Debug output */
  void OutputModel();

 private:
};
}  // namespace s21
#endif  // MODEL_MODEL_H_

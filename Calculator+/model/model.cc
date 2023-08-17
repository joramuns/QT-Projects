#include "model.h"

namespace s21 {
/* Modifiers */
void Model::Convert() {
  ClearPostfix();
  for (const auto &item : GetInfixData()) {
    if (item.IsOperator()) {
      AddOperator(item);
    } else {
      AddOperand(item);
    }
  }
  Finalize();
}

/* Calculators */
double Model::Evaluate() {
  Element result;
  std::stack<Element> eval_stack;
  for (const auto &item : GetPostfixExpr()) {
    if (item.IsOperator()) {
      OpType math_operator = static_cast<OpType>(item.GetValue());
      Element a = eval_stack.top();
      eval_stack.pop();
      if (item.GetPriority() < 2) {
        Element b = eval_stack.top();
        eval_stack.pop();
        result = Calculate(a, b, math_operator);
      } else {
        result = Calculate(a, math_operator);
      }
      Element result_elem(result);
      eval_stack.push(result_elem);
    } else {
      eval_stack.push(item);
    }
  }
  return 1.0;
}

/* Debug output */
void Model::OutputModel() {
  std::cout << "Infix notation: ";
  for (const auto &item : GetInfixData()) {
    std::cout << item << " ";
  }
  std::cout << std::endl << "Polish notation: ";
  for (const auto &item : GetPostfixExpr()) {
    std::cout << item << " ";
  }
  if (GetQueue().size()) {
    std::cout << std::endl << "Queue stack: ";
    for (const auto &item : GetQueue()) {
      std::cout << item << " ";
    }
  }
}

Element Model::Calculate(const Element &a, const Element &b,
                         OpType math_operator) const noexcept {
  Element result;
  if (math_operator == OpType::kAddition) {
    result = a + b;
  } else if (math_operator == OpType::kSubtraction) {
    result = a - b;
  } else if (math_operator == OpType::kModulus) {
    result = a % b;
  } else if (math_operator == OpType::kMultiplication) {
    result = a * b;
  } else if (math_operator == OpType::kDivision) {
    result = a / b;
  }

  return result;
}

Element Model::Calculate(const Element &a,
                         OpType math_operator) const noexcept {
  Element result;
  if (math_operator == OpType::kSin) {
    result = a.sin();
  }

  return result;
}
}  // namespace s21

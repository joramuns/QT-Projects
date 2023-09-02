#include "model.h"

namespace s21 {
/* Modifiers */
void Model::Convert() noexcept {
  ClearPostfixExpr();
  for (const auto &item : GetInfixData()) {
    if (item->IsOperator()) {
      AddOperator(*item);
    } else {
      AddOperand(*item);
    }
  }
  PopAndPushAll();
}

void Model::ClearModel() noexcept {
  ClearInfixExpr();
  ClearPostfixExpr();
}

/* Calculators */
double Model::Evaluate() noexcept {
  Convert();
  Element result;
  std::stack<Element> eval_stack;
  for (const auto &item : GetPostfixExpr()) {
    if (item.IsOperator()) {
      OpType math_operator = static_cast<OpType>(item.GetValue());
      Element b = eval_stack.top();
      eval_stack.pop();
      int operator_priority = item.GetPriority();
      if (operator_priority <= 1) {
        Element a = eval_stack.top();
        eval_stack.pop();
        result = Calculate(a, b, math_operator);
      } else {
        result = Calculate(b, math_operator);
      }
      eval_stack.push(result);
    } else {
      eval_stack.push(item);
    }
  }
  return eval_stack.top().GetValue();
}

/* Debug output */
void Model::OutputModel() noexcept {
  std::cout << "Infix notation: ";
  for (const auto &item : GetInfixData()) {
    std::cout << *item << " ";
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
  std::cout << std::endl;
}

Element Model::Calculate(const Element &a, const Element &b,
                         OpType math_operator) const noexcept {
  Element result;
  if (math_operator == OpType::kAddition || math_operator == OpType::kUnaryAddition) {
    result = a + b;
  } else if (math_operator == OpType::kSubtraction || math_operator == OpType::kUnarySubtraction) {
    result = a - b;
  } else if (math_operator == OpType::kModulus) {
    result = a % b;
  } else if (math_operator == OpType::kMultiplication) {
    result = a * b;
  } else if (math_operator == OpType::kDivision) {
    result = a / b;
  } else if (math_operator == OpType::kPower) {
    result = a ^ b;
  }

  return result;
}

Element Model::Calculate(const Element &a,
                         OpType math_operator) const noexcept {
  Element result;
  if (math_operator == OpType::kSin) {
    result = a.sin();
  } else if (math_operator == OpType::kCos) {
    result = a.cos();
  } else if (math_operator == OpType::kTan) {
    result = a.tan();
  } else if (math_operator == OpType::kAsin) {
    result = a.asin();
  } else if (math_operator == OpType::kAcos) {
    result = a.acos();
  } else if (math_operator == OpType::kAtan) {
    result = a.atan();
  } else if (math_operator == OpType::kSqrt) {
    result = a.sqrt();
  } else if (math_operator == OpType::kLn) {
    result = a.ln();
  } else if (math_operator == OpType::kLog) {
    result = a.log();
  }

  return result;
}

std::string Model::GetResult() noexcept {
  std::string result{};
  if (ValidateExpr()) {
    result = "Malformed expression";
  } else {
    double value = Evaluate();
    std::stringstream ss;
    ss << value;
    result = GetInfixString() + " = " + ss.str();
  }

  return result;
}

}  // namespace s21

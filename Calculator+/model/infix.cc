#include "infix.h"

#include <QDebug>

namespace s21 {
void InfixExpr::AddElement(const char number) noexcept {
  if (number == 'x' || LastIsOperator() || LastIsVariable()) {
    s21::Element e_number{number};
    AddElement(e_number);
  } else {
    AppendNumber(number);
  }
}

void InfixExpr::AddElement(const Element &token) noexcept {
  infix_data_.push_back(token);
  if (token.IsVariable()) {
    /* Interesting fact: insertions in deque invalidate iterators, but not
     * references to elements */
    var_array_.push_back(&infix_data_.back());
  } else if (token.GetPriority() == Element::PriorityType::kTrigonometry) {
    infix_data_.push_back(Element{Element::OperatorType::kBracketOpen});
  }
};

void InfixExpr::DelElement() noexcept { infix_data_.pop_back(); }

int InfixExpr::ValidateExpr() noexcept {
  int ex_code = 0;
  auto iter_begin = infix_data_.begin();

  ex_code = SizeValid(iter_begin);
  if (!ex_code) ex_code = EndValid();
  if (!ex_code) ex_code = BeginValid(iter_begin);
  if (!ex_code) ex_code = MiddleValid(iter_begin);

  return ex_code;
}

void InfixExpr::ClearInfixExpr() noexcept {
  infix_data_.clear();
  var_array_.clear();
}

void InfixExpr::AppendNumber(const char number) noexcept {
  infix_data_.back().AppendNumber(number);
}

void InfixExpr::SetVariables(const std::string &str_number) noexcept {
  double number = std::stod(str_number);
  for (auto &item : var_array_) {
    item->SetValue(number);
  }
}

std::deque<Element> InfixExpr::GetInfixData() const noexcept {
  return infix_data_;
}

std::string InfixExpr::GetInfixString() const noexcept {
  std::string result{};
  for (const auto &item : infix_data_) {
    result += *item + " ";
  }
  return result;
}

bool InfixExpr::LastIsOperator() const noexcept {
  return infix_data_.empty() ? true : infix_data_.back().IsOperator();
}

bool InfixExpr::LastIsVariable() const noexcept {
  return infix_data_.empty() ? false : infix_data_.back().IsVariable();
}

int InfixExpr::SizeValid(const elem_iterator iter_begin) {
  int ex_code = 0;
  int expression_size = infix_data_.size();
  if (!expression_size || (expression_size == 1 && iter_begin->IsOperator())) {
    /* Only operator in expression */
    ex_code = 3;
  }
  return ex_code;
}

int InfixExpr::BeginValid(const elem_iterator iter_begin) {
  int ex_code = 0;
  /* Check operator going first */
  if (iter_begin->IsOperator()) {
    int start_op_priority = iter_begin->GetPriority();
    if (start_op_priority == Element::PriorityType::kMulDivModPow) {
      /* Not unary, not open bracket first - error */
      ex_code = 2;
    } else if (start_op_priority == Element::PriorityType::kSubAdd) {
      iter_begin->SetUnary();
    }
  }
  return ex_code;
}

int InfixExpr::EndValid() {
  /* Check end expression */
  int ex_code = 0;
  if (infix_data_.back().IsOperator() &&
      (int)infix_data_.back().GetValue() !=
          Element::OperatorType::kBracketClose) {
    /* Bad end expression */
    ex_code = 4;
  }
  return ex_code;
}

int InfixExpr::MiddleValid(elem_iterator iter_begin) {
  int ex_code = 0;
  /* Check duplicate operators + count brackets */
  int bracket_counter = 0;
  const auto iter_end = infix_data_.end();
  auto iter_next = std::next(iter_begin);
  for (; iter_begin != iter_end && !ex_code; ++iter_begin, ++iter_next) {
    if (iter_begin->IsOperator()) {
      int type_begin = (int)iter_begin->GetValue();
      if (type_begin == Element::OperatorType::kBracketOpen) {
        ++bracket_counter;
      } else if (type_begin == Element::OperatorType::kBracketClose) {
        --bracket_counter;
      }
      if (bracket_counter < 0) {
        /* Brackets error */
        ex_code = 1;
      }
      if (iter_next != iter_end && iter_next->IsOperator()) {
        ex_code = DoubleOperator(iter_begin, iter_next);
      } else if (iter_next != iter_end &&
                 type_begin == Element::OperatorType::kBracketClose) {
        /* No operator between bracket and num */
        ex_code = 5;
      }
      /*** NUM - OPERATOR case ***/
    } else if (iter_next != iter_end && iter_next->IsOperator()) {
      if (iter_next->GetPriority() == Element::PriorityType::kTrigonometry ||
          (int)iter_next->GetValue() == Element::OperatorType::kBracketOpen) {
        /* No operator between bracket and num */
        ex_code = 5;
      }
    } else if (iter_next != iter_end) {
      /*** NUM - NUM case ***/
      ex_code = 13;
    }
  }
  if (bracket_counter) {
    /* Brackets error */
    ex_code = 1;
  }

  return ex_code;
}

int InfixExpr::DoubleOperator(const elem_iterator op_first,
                              const elem_iterator op_second) {
  int ex_code = 0;
  int type_first = (int)op_first->GetValue();
  int type_second = (int)op_second->GetValue();
  int priority_first = op_first->GetPriority();
  int priority_second = op_second->GetPriority();
  if (type_first == Element::OperatorType::kBracketOpen) {
    if (priority_second == Element::PriorityType::kMulDivModPow) {
      /* Open bracket and muldivmodpow */
      ex_code = 7;
    } else if (type_second == Element::OperatorType::kBracketClose) {
      /* Brackets error - empty brackets */
      ex_code = 1;
    } else if (priority_second == Element::PriorityType::kSubAdd) {
      op_second->SetUnary();
    }
  } else if (type_first == Element::OperatorType::kBracketClose) {
    if (priority_second == Element::PriorityType::kTrigonometry) {
      /* Close bracket and trigonometry */
      ex_code = 8;
    } else if (type_second == Element::OperatorType::kBracketOpen) {
      /* Brackets error - close then open without operator */
      ex_code = 1;
    }
  } else if (priority_first == Element::PriorityType::kSubAdd ||
             priority_first == Element::PriorityType::kMulDivModPow) {
    if (priority_second == Element::PriorityType::kMulDivModPow ||
        priority_second == Element::PriorityType::kSubAdd ||
        type_second == Element::OperatorType::kBracketClose) {
      /* Double operator error */
      ex_code = 9;
    }
  }
  return ex_code;
}
}  // namespace s21

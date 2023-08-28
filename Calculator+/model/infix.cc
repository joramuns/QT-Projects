#include "infix.h"

#include <QDebug>

namespace s21 {
void InfixExpr::AddElement(const char number) noexcept {
  if (LastIsOperator()) {
    s21::Element e_number{number};
    AddElement(e_number);
  } else {
    AppendNumber(number);
  }
}

void InfixExpr::AddElement(const Element &token) noexcept {
  infix_data_.push_back(token);
  if (token.GetPriority() == 3) {
    infix_data_.push_back(Element{Element::OperatorType::kBracketOpen});
  }
};

void InfixExpr::DelElement() noexcept { infix_data_.pop_back(); }

int InfixExpr::ValidateExpr() noexcept {
  int result = 0;
  auto iter_begin = infix_data_.begin();

  result = SizeValid(iter_begin);
  if (!result) result = EndValid();
  if (!result) result = BeginValid(iter_begin);
  if (!result) result = MiddleValid(iter_begin);

  return result;
}

void InfixExpr::ClearInfixExpr() noexcept { infix_data_.clear(); }

void InfixExpr::AppendNumber(const char number) noexcept {
  infix_data_.back().AppendNumber(number);
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

int InfixExpr::SizeValid(const elem_iterator iter_begin) {
  int result = 0;
  int expression_size = infix_data_.size();
  if (!expression_size || (expression_size == 1 && iter_begin->IsOperator())) {
    /* Only operator in expression */
    result = 3;
  }
  return result;
}

int InfixExpr::BeginValid(const elem_iterator iter_begin) {
  int result = 0;
  /* Check operator going first */
  if (iter_begin->IsOperator()) {
    int start_op_priority = iter_begin->GetPriority();
    if (start_op_priority == Element::PriorityType::kMulDivModPow) {
      /* Not unary, not open bracket first - error */
      result = 2;
    } else if (start_op_priority == Element::PriorityType::kSubAdd) {
      /* if (!iter_next->IsOperator() || */
      /*     (iter_next->IsOperator() && */
      /*      (iter_next->GetPriority() == Element::OperatorType::kBracketOpen
       * || */
      /*       iter_next->GetPriority() == */
      /*           Element::PriorityType::kTrigonometry))) { */
      iter_begin->SetUnary();
      /* } */
    }
  }
  return result;
}

int InfixExpr::EndValid() {
  /* Check end expression */
  int result = 0;
  if (infix_data_.back().IsOperator() &&
      infix_data_.back().GetValue() != Element::OperatorType::kBracketClose) {
    /* Bad end expression */
    result = 4;
  }
  return result;
}

int InfixExpr::MiddleValid(elem_iterator iter_begin) {
  int result = 0;
  /* Check duplicate operators + count brackets */
  int bracket_counter = 0;
  const auto iter_end = infix_data_.end();
  auto iter_next = std::next(iter_begin);
  for (; iter_begin != iter_end && !result; ++iter_begin, ++iter_next) {
    if (iter_begin->IsOperator()) {
      int type_begin = iter_begin->GetValue();
      if (type_begin == Element::OperatorType::kBracketOpen) {
        ++bracket_counter;
      } else if (type_begin == Element::OperatorType::kBracketClose) {
        --bracket_counter;
      }
      if (bracket_counter < 0) {
        /* Brackets error */
        result = 1;
      }
      if (iter_next != iter_end && iter_next->IsOperator()) {
        result = DoubleOperator(type_begin, (int)iter_next->GetValue());
      } else if (iter_next != iter_end &&
                 type_begin == Element::OperatorType::kBracketClose) {
        /* No operator between bracket and num */
        result = 5;
      }
    } else if (iter_next != iter_end && iter_next->IsOperator() &&
               iter_next->GetValue() == Element::OperatorType::kBracketOpen) {
      /* No operator between bracket and num */
      result = 5;
    }
  }
  if (bracket_counter) {
    /* Brackets error */
    result = 1;
  }

  return result;
}

int InfixExpr::DoubleOperator(const int type_first, const int type_second) {
  int result = 0;
  if (type_first == type_second) {
    /* Two identical operators error */
    result = 6;
  } else if (type_first == Element::OperatorType::kBracketOpen && type_second == Element::OperatorType::kBracketClose) {
    /* Brackets error */
    result = 1;
  }
  return result;
}
}  // namespace s21

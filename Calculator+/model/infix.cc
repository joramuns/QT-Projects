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
  int bracket_counter = 0;
  const auto iter_end = infix_data_.end();
  auto iter_begin = infix_data_.begin();
  auto iter_next = std::next(iter_begin);
  /* Check operator going first */
  if (iter_begin->IsOperator()) {
    int start_op_priority = iter_begin->GetPriority();
    int start_op_type = (int)iter_begin->GetValue();
    if (iter_next == iter_end) {
      result = 3;
    } else if (start_op_priority == Element::PriorityType::kMulDivModPow ||
               start_op_type == Element::OperatorType::kBracketClose) {
      /* Not unary, not open bracket first - error */
      result = 2;
    } else if (start_op_priority == Element::PriorityType::kSubAdd) {
        qDebug("infix start_op_priority == %d, start_op_type == %d, next_op_priority == %d",
               start_op_priority, start_op_type, iter_next->GetPriority());
      if (!iter_next->IsOperator() ||
          (iter_next->IsOperator() &&
           iter_next->GetPriority() == Element::PriorityType::kTrigonometry)) {
        iter_begin->SetUnary();
      }
    }
  }
  /* Check duplicate operators + count brackets */
  for (; iter_begin != iter_end && !result; ++iter_begin, ++iter_next) {
    if (iter_begin->IsOperator()) {
      int type_begin = iter_begin->GetValue();
      if (type_begin == Element::OperatorType::kBracketOpen) {
        ++bracket_counter;
      } else if (type_begin == Element::OperatorType::kBracketClose) {
        --bracket_counter;
      }
      /* Brackets error */
      if (bracket_counter < 0) {
        result = 1;
      }
      if (iter_next != iter_end && iter_next->IsOperator()) {
      }
    }
  }
  /* Brackets error */
  if (bracket_counter) {
    result = 1;
  }
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
  /* return true; */
  return infix_data_.empty() ? true : infix_data_.back().IsOperator();
}
}  // namespace s21

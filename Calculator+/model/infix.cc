#include "infix.h"

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
    if (start_op_priority == 2 ||
        start_op_type == Element::OperatorType::kBracketClose) {
      result = 2;
    } else if (start_op_type == Element::OperatorType::kSubtraction &&
               !iter_next->IsOperator()) {
      iter_next->ChangeSign();
      infix_data_.pop_front();
      ++iter_begin;
      ++iter_next;
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
      if (bracket_counter < 0) {
        result = 1;
      }
      if (iter_next != iter_end && iter_next->IsOperator()) {
      }
    }
  }
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

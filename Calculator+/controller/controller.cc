#include "controller.h"

#include <QDebug>
#include <QPushButton>

namespace s21 {
Controller::Controller(CalcWindow *cview, Model *cmodel)
    : view_(cview), model_(cmodel) {
  /* Clear button signal */
  connect(view_->clear_, &QPushButton::released, this,
          &Controller::ClearButton);

  /* Num buttons signals */
  for (const auto &item : view_->num_buttons_) {
    connect(item, &QPushButton::released, this, &Controller::NumButton);
  }

  /* Operator buttons signals */
  for (const auto &item : view_->operator_buttons_) {
    connect(item, &QPushButton::released, this, &Controller::OperButton);
  }

  /* Input lines signals */
  connect(view_->input_lines_[0], &QLineEdit::textEdited, this,
          &Controller::VariableSet);

  /* Evaluate button signal */
  connect(view_->eval_, &QPushButton::released, this, &Controller::EvalButton);
}

void Controller::ClearButton() noexcept {
  model_->ClearModel();
  Render();
}

void Controller::NumButton() noexcept {
  QString text_button = static_cast<QPushButton *>(sender())->text();
  char char_number = text_button[0].toLatin1();
  model_->AddElement(char_number);
  Render();
}

void Controller::OperButton() noexcept {
  OperatorButton *button = static_cast<OperatorButton *>(sender());
  int operator_type = button->GetType();
  s21::Element e_operator{operator_type};
  model_->AddElement(e_operator);
  Render();
}

void Controller::EvalButton() noexcept {
  std::string result = model_->GetResult();
  view_->results_display_->addItem(QString::fromStdString(result));
  view_->results_display_->scrollToBottom();
}

void Controller::VariableSet() noexcept {
  QString input_value = static_cast<QLineEdit *>(sender())->text();
  if (!input_value.isEmpty()) {
    std::string std_input_value = input_value.toStdString();
    model_->SetVariables(std_input_value);
  }
}
void Controller::Render() const noexcept {
  std::string infix_line = model_->GetInfixString();
  view_->display_->setText(QString::fromStdString(infix_line));
}

}  // namespace s21

#include "controller.h"

#include <QDebug>
#include <QPushButton>

namespace s21 {
Controller::Controller(CalcWindow *cview, Model *cmodel)
    : view_(cview), model_(cmodel) {
  for (double i = 0; i < 10; ++i)
    connect(cview->num_buttons_[i], &QPushButton::released, this,
            [=]() { NumButton(i); });
}

void Controller::NumButton(const double number) {
  if (model_->LastIsOperator()) {
    s21::Element e_number{number + 1};
    model_->AddElement(e_number);
  } else {
    model_->AppendNumber(number + 1);
  }
  Render();
}

void Controller::Render() const noexcept {
  std::string infix_line = model_->GetInfixString();
  view_->display_->setText(QString::fromStdString(infix_line));
}

}  // namespace s21

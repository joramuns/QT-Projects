#include "operatorbutton.h"

namespace s21 {
OperatorButton::OperatorButton(const int type, const QString &text,
                               QWidget *parent)
    : QPushButton(text, parent), button_type_(type) {}

int OperatorButton::GetType() { return button_type_; }

}  // namespace s21

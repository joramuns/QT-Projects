#include "tbutton.h"

namespace s21 {
TButton::TButton(const QString &label) : QPushButton(label) {
  setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
  setStyleSheet("background-color: #893101; font: white;");
}
}  // namespace s21

#ifndef VIEW_OPERATORBUTTON_H_
#define VIEW_OPERATORBUTTON_H_

#include <QPushButton>

namespace s21 {
class OperatorButton : public QPushButton {
 public:
  OperatorButton(const int type, const QString &text, QWidget *parent);
  int GetType();

 private:
  int button_type_;
};
}  // namespace s21
#endif  // VIEW_OPERATORBUTTON_H_

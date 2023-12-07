#ifndef VIEW_TBUTTON_H_
#define VIEW_TBUTTON_H_

#include <QPushButton>

#define BUTTON_SIZE 80

namespace s21 {
class TButton final : public QPushButton {
  Q_OBJECT
 public:
  explicit TButton(const QString &text);
};
}  // namespace s21

#endif  // VIEW_TBUTTON_H_

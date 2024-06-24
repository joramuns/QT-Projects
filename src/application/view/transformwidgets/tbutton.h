#ifndef VIEW_TBUTTON_H_
#define VIEW_TBUTTON_H_

#include <QPushButton>

#define BUTTON_SIZE 80

namespace s21 {
/// @brief Класс определяющий базовые свойства кнопок, отвечающих за
/// трансформацию 3-х мерного объекта
class TButton final : public QPushButton {
  Q_OBJECT
 public:
  /// @brief Конструктор, инициализирующий кнопку и определяющий ее базовое
  /// поведение
  /// @param label Отображаемый на кнопке текст
  explicit TButton(const QString &label);
};
}  // namespace s21

#endif  // VIEW_TBUTTON_H_

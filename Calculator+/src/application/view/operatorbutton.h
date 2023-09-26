/**
 * @brief Заголовочный файл с описанием класса OperatorButton
 *
 * Данный класс наследуется от стандартного QT класса QPushButton. Изменен
 * конструктор, который принимает в качестве аргументов не только надпись на
 * кнопке и родительский виджет, но и тип оператора. Необходимо для облегчения
 * работы класса контроллера.
 */
#ifndef VIEW_OPERATORBUTTON_H_
#define VIEW_OPERATORBUTTON_H_

#include <QPushButton>

namespace s21 {
/**
 * @brief Класс кнопки оператора, унаследован от QPushButton, но дополнительно
 * несет в себе информацию о типе оператора.
 */
class OperatorButton : public QPushButton {
 public:
  /**
   * @brief Конструктор класса
   *
   * @param type Тип оператора в соответствии с типами класса модели
   * @param text Текст на кнопке
   * @param parent Родительский виджет, получающий владение объектом
   */
  OperatorButton(const int type, const QString &text, QWidget *parent);
  /**
   * @brief Функция, возвращающая значение типа оператора
   *
   * @return Тип оператора
   */
  int GetType();

 private:
  /**
   * @brief Тип оператора кнопки
   */
  int button_type_;
};

}  // namespace s21
#endif  // VIEW_OPERATORBUTTON_H_

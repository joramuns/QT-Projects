#ifndef VIEW_SCALEBUTTONS_H_
#define VIEW_SCALEBUTTONS_H_

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "tbutton.h"

#define SCALE 2

namespace s21 {
/// @brief Класс служит для инициализации кнопок управления масштабом
class ScaleButtons final : public QWidget {
  Q_OBJECT

public:
  /// @brief Констурктор по умолчанию
  ScaleButtons();

public slots:
  /// @brief Слот выпускающий сигнал обработчику
  void ScaleSlot(double value, char axis, int type);

signals:
  /// @brief Сигнал обработчику, посылаемый при нажатии кнопок управления
  /// масштабом
  void ScaleSignal(double value, char axis, int type);

private:
  /// @brief Инициализация кнопок управления
  void InitFields();

  /// @brief Связка кнопок со слотами обработчиками сигналов
  void ConnectFields();

  /// @brief Инициализация "макетов" и расположение на них кнопок управления
  /// масштабом
  void InitLayouts();

private:
  QPushButton *increase_; ///< указатель на объект кнопки инкремента масштаба
  QPushButton *decrease_; ///< указатель на объект кнопки декремента масштаба

  QDoubleSpinBox
      *step_; ///< указатель на объект поля ввода значения величины масштаба
};
} // namespace s21

#endif // VIEW_SCALEBUTTONS_H_

#ifndef VIEW_TRANSFORM_TAB_H_
#define VIEW_TRANSFORM_TAB_H_

#include <QTabWidget>

#include "scale_buttons.h"
#include "transform_buttons.h"

namespace s21 {
/// @brief Класс инициализирующий "макеты" вкладок кнопок
class TransformationTab final : public QTabWidget {
  Q_OBJECT

public:
  /// @brief Конструктор по умолчанию
  TransformationTab();

private slots:
  /// @brief Слот выпускающий сигнал ??????????????????????
  void TransformTabSlot(double value, char axis, int type);

signals:
  void TransformTabSignal(double value, char axis, int type);

private:
  /// @brief Метод инициализирует вкладки, которые в свою очередь запускают
  /// инициализацию кнопок и выстраивают расположение
  void InitFields();

  /// @brief
  void ConnectFields();

private:
  TransformButtons *rotate_buttons_; ///< указатель на объект вкладки кнопок вращения
  TransformButtons *move_buttons_;   ///< укзатель на объект влкадки кнопок перемещения
  ScaleButtons *scale_buttons_;      ///< укзатель на объект вкладки кнопок масштабирования
};
} // namespace s21

#endif // VIEW_TRANSFORM_TAB_H_

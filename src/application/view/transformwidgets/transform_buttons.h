#ifndef TRANSFORM_BUTTONS_H_
#define TRANSFORM_BUTTONS_H_

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "tbutton.h"

#define X_INCREASE_ROW 1
#define X_INCREASE_COL 2
#define Y_INCREASE_ROW 0
#define Y_INCREASE_COL 1
#define Z_INCREASE_ROW 0
#define Z_INCREASE_COL 2
#define X_DECREASE_ROW 1
#define X_DECREASE_COL 0
#define Y_DECREASE_ROW 1
#define Y_DECREASE_COL 1
#define Z_DECREASE_ROW 0
#define Z_DECREASE_COL 0

#define ROTATE 1
#define MOVE -1

#define SPACING 30

namespace s21 {
/// @brief Класс служит для инициализации и организации на "макете" кнопок
/// управления 3-х мерным объектом
class TransformButtons final : public QWidget {
  Q_OBJECT

public:
  /// @brief Конструктор по умолчанию - удален
  TransformButtons() = delete;

  /// @brief Конструктор инициализирующий кнопки управления афинными
  /// трансформациями
  /// @param labels Двумерный массив символов для нанесения их на каждую кнопку
  /// @param type Указывает тип трансформации (перемещение/вращение)
  TransformButtons(const QChar labels[2][3], int type);

public slots:
  /// @brief Слот выпускающий сигнал для обработки нажатия на кнопку
  void TransformSlot(double value, char axis, int type);

signals:
  /// @brief Сигнал выпускаемый для обработки нажатия на кнопку
  void TransformSignal(double value, char axis, int type);

private:
  /// @brief Метод инициализирующий объекты кнопок
  /// @param labels Двумерный массив символов для нанесения их на каждую кнопку
  void InitFields(const QChar labels[2][3]);

  /// @brief Метод связывающий нажатие кнопок со слотом
  /// @param type Указывает тип трансформаций (перемещение/вращение)
  void ConnectFields(int type);

  /// @brief Метод инициализирующий "макет" и располагающий на нем кнопки
  void InitLayouts();

private:
  TButton *x_increase_; ///< укзатель на объект кнопки инкремента (вдоль/вокруг)
                        ///< оси Х
  TButton *x_decrease_; ///< укзатель на объект кнопки декремента (вдоль/вокруг)
                        ///< оси Х

  TButton *y_increase_; ///< укзатель на объект кнопки инкремента (вдоль/вокруг)
                        ///< оси Y
  TButton *y_decrease_; ///< укзатель на объект кнопки декремента (вдоль/вокруг)
                        ///< оси Y

  TButton *z_increase_; ///< укзатель на объект кнопки инкремента (вдоль/вокруг)
                        ///< оси Z
  TButton *z_decrease_; ///< укзатель на объект кнопки инкремента (вдоль/вокруг)
                        ///< оси Z

  QDoubleSpinBox *step_; ///< указатель на объект поля ввода значения величины
                         ///< трансофрмации (перемещение/вращение)
};
} // namespace s21

#endif // TRANSFORM_BUTTONS_H_

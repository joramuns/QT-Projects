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

#define ROTATE 0
#define MOVE 1

#define SPACING 30

namespace s21 {
class TransformButtons final : public QWidget {
  Q_OBJECT

 public:
  TransformButtons() = delete;
  TransformButtons(const QChar labels[2][3], int type);

 public slots:
  void TransformSlot(double value, char axis, int type);

 signals:
  void TransformSignal(double value, char axis, int type);

 private:
  void InitFields(const QChar labels[2][3]);
  void ConnectFields(int type);
  void InitLayouts();

 private:
  TButton *x_increase_;
  TButton *x_decrease_;

  TButton *y_increase_;
  TButton *y_decrease_;

  TButton *z_increase_;
  TButton *z_decrease_;

  QDoubleSpinBox *step_;
};
}  // namespace s21

#endif  // TRANSFORM_BUTTONS_H_

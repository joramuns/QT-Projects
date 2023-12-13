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
class ScaleButtons final : public QWidget {
  Q_OBJECT

 public:
  ScaleButtons();

 public slots:
  void ScaleSlot(double value, char axis, int type);

 signals:
  void ScaleSignal(double value, char axis, int type);

 private:
  void InitFields();
  void ConnectFields();
  void InitLayouts();

 private:
  QPushButton *increase_;
  QPushButton *decrease_;

  QDoubleSpinBox *step_;
};
}  // namespace s21

#endif  // VIEW_SCALEBUTTONS_H_

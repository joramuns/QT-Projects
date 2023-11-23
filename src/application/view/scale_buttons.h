#ifndef VIEW_SCALEBUTTONS_H_
#define VIEW_SCALEBUTTONS_H_

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "tbutton.h"

namespace s21 {
class ScaleButtons final : public QWidget {
  Q_OBJECT

 public:
  ScaleButtons();

 private:
  void InitFields();
  void InitLayouts();

 private:
  QPushButton *increase_;
  QPushButton *decrease_;

  QDoubleSpinBox *step_;
};
}  // namespace s21

#endif  // VIEW_SCALEBUTTONS_H_

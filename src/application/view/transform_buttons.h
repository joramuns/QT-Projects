#ifndef TRANSFORM_BUTTONS_H_
#define TRANSFORM_BUTTONS_H_

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <string>
#include <vector>

namespace s21 {
class TransformButtons final : public QWidget {
  Q_OBJECT

 public:
  TransformButtons() = delete;
  explicit TransformButtons(const QChar labels[2][3]);

 private:
  QPushButton *x_increase_;
  QPushButton *x_decrease_;

  QPushButton *y_increase_;
  QPushButton *y_decrease_;

  QPushButton *z_increase_;
  QPushButton *z_decrease_;

  QDoubleSpinBox *step_;
};

class ScaleButtons final : public QWidget {
  Q_OBJECT

 public:
  ScaleButtons();

 private:
  QPushButton *increase_;
  QPushButton *decrease_;

  QDoubleSpinBox *step_;
};
}  // namespace s21

#endif  // TRANSFORM_BUTTONS_H_

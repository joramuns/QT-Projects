#ifndef TRANSFORM_BUTTONS_H_
#define TRANSFORM_BUTTONS_H_

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include <vector>

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

#define L_STEP_ROW 2
#define L_STEP_COL 0
#define STEP_ROW 2
#define STEP_COL 1

#define S_INCREASE_ROW 0
#define S_INCREASE_COL 0
#define S_DECREASE_ROW 0
#define S_DECREASE_COL 1

#define S_L_STEP_ROW 1
#define S_L_STEP_COL 0
#define S_STEP_ROW 1
#define S_STEP_COL 1

#define BUTTON_SIZE 80
#define SPACING 30

namespace s21 {
class TransformButtons final : public QWidget {
  Q_OBJECT

 public:
  TransformButtons() = delete;
  TransformButtons(const QChar labels[2][3], int type);

 private slots:
  void HandleTransform(double value, char axis, int type);

 signals:
  void EmitTransform(double value, char axis, int type);

 private:
  void InitFields(const QChar labels[2][3]);
  void ConnectFields(int type);
  void InitLayouts();

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
  void InitFields();
  void InitLayouts();

 private:
  QPushButton *increase_;
  QPushButton *decrease_;

  QDoubleSpinBox *step_;
};

class TButton final : public QPushButton {
  Q_OBJECT
 public:
  explicit TButton(const QString &text);
};

class TransformationTab final : public QTabWidget {
  Q_OBJECT

 public:
  TransformationTab();

 private:
  TransformButtons *rotate_buttons_;
  TransformButtons *move_buttons_;
  ScaleButtons *scale_buttons_;
};
}  // namespace s21

#endif  // TRANSFORM_BUTTONS_H_

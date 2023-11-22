#include "transform_buttons.h"

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
#define STEP_ROW 2
#define STEP_COL 0

namespace s21 {
TransformButtons::TransformButtons(const QChar labels[2][3]) : QWidget(nullptr) {
  layout = new QGridLayout;
  setLayout(layout);

  x_increase_ = new QPushButton('X' + labels[X_INCREASE_ROW][X_INCREASE_COL]);
  x_decrease_ = new QPushButton(labels[X_DECREASE_ROW][X_DECREASE_COL] + 'X');

  y_increase_ = new QPushButton('Y' + labels[Y_INCREASE_ROW][Y_INCREASE_COL]);
  y_decrease_ = new QPushButton('Y' + labels[Y_DECREASE_ROW][Y_DECREASE_COL]);

  z_increase_ = new QPushButton('Z' + labels[Z_INCREASE_ROW][Z_INCREASE_COL]);
  z_decrease_ = new QPushButton(labels[Z_DECREASE_ROW][Z_DECREASE_COL] + 'Z');

  step_ = new QDoubleSpinBox;

  layout->addWidget(x_increase_, X_INCREASE_ROW, X_INCREASE_COL);
  layout->addWidget(x_decrease_, X_DECREASE_ROW, X_DECREASE_COL);
  layout->addWidget(y_increase_, Y_INCREASE_ROW, Y_INCREASE_COL);
  layout->addWidget(y_decrease_, Y_DECREASE_ROW, Y_DECREASE_COL);
  layout->addWidget(z_increase_, Z_INCREASE_ROW, Z_INCREASE_COL);
  layout->addWidget(z_decrease_, Z_DECREASE_ROW, Z_DECREASE_COL);
  layout->addWidget(new QLabel("Step: "), STEP_ROW, STEP_COL);
  layout->addWidget(step_, STEP_ROW, STEP_COL + 1, 1, 2);
}
}  // namespace s21

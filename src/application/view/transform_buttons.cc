#include "transform_buttons.h"

namespace s21 {
TransformButtons::TransformButtons(const QChar labels[2][3])
    : QWidget(nullptr) {
  setFixedSize(3 * BUTTON_SIZE + 2 * SPACING,
               2 * SPACING + 2 * BUTTON_SIZE + BUTTON_SIZE / 2);
  QGridLayout *layout = new QGridLayout;
  layout->setSpacing(SPACING);
  setLayout(layout);

  x_increase_ = new TButton('X' + labels[X_INCREASE_ROW][X_INCREASE_COL]);
  x_decrease_ = new TButton(labels[X_DECREASE_ROW][X_DECREASE_COL] + 'X');

  y_increase_ = new TButton('Y' + labels[Y_INCREASE_ROW][Y_INCREASE_COL]);
  y_decrease_ = new TButton('Y' + labels[Y_DECREASE_ROW][Y_DECREASE_COL]);

  z_increase_ = new TButton('Z' + labels[Z_INCREASE_ROW][Z_INCREASE_COL]);
  z_decrease_ = new TButton(labels[Z_DECREASE_ROW][Z_DECREASE_COL] + 'Z');

  step_ = new QDoubleSpinBox;

  layout->addWidget(x_increase_, X_INCREASE_ROW, X_INCREASE_COL);
  layout->addWidget(x_decrease_, X_DECREASE_ROW, X_DECREASE_COL);
  layout->addWidget(y_increase_, Y_INCREASE_ROW, Y_INCREASE_COL);
  layout->addWidget(y_decrease_, Y_DECREASE_ROW, Y_DECREASE_COL);
  layout->addWidget(z_increase_, Z_INCREASE_ROW, Z_INCREASE_COL);
  layout->addWidget(z_decrease_, Z_DECREASE_ROW, Z_DECREASE_COL);
  layout->addWidget(new QLabel("Step: "), L_STEP_ROW, L_STEP_COL);
  layout->addWidget(step_, STEP_ROW, STEP_COL, 1, 2);
}

ScaleButtons::ScaleButtons() : QWidget(nullptr) {
  setFixedSize(2 * BUTTON_SIZE +  SPACING,
               SPACING + BUTTON_SIZE + BUTTON_SIZE / 2);
  QGridLayout *layout = new QGridLayout;
  layout->setSpacing(SPACING);
  setLayout(layout);

  increase_ = new TButton("+");
  decrease_ = new TButton("-");

  step_ = new QDoubleSpinBox;

  layout->addWidget(increase_, S_INCREASE_ROW, S_INCREASE_COL);
  layout->addWidget(decrease_, S_DECREASE_ROW, S_DECREASE_COL);
  layout->addWidget(new QLabel("Step: "), S_L_STEP_ROW, S_L_STEP_COL);
  layout->addWidget(step_, S_STEP_ROW, S_STEP_COL);
}

TButton::TButton(const QString &label) : QPushButton(label) {
  setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
  /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum); */
  setStyleSheet("background-color: #893101; font: white;");
}

TransformationTab::TransformationTab() {
  const QChar rotate_labels[2][3] = {
      {QChar(0x000027F2), QChar(0x000027F3), QChar(0x000027F3)},
      {QChar(0x000027F2), QChar(0x000027F2), QChar(0x000027F3)}};
  rotate_buttons_ = new TransformButtons(rotate_labels);

  const QChar move_labels[2][3] = {
      {QChar(0x00002357), QChar(0x00002191), QChar(0x00002350)},
      {QChar(0x00002190), QChar(0x00002193), QChar(0x00002192)}};
  move_buttons_ = new TransformButtons(move_labels);

  scale_buttons_ = new ScaleButtons();
  
  addTab(rotate_buttons_, "Rotation");
  addTab(move_buttons_, "Movement");
  addTab(scale_buttons_, "Scaling");
}
}  // namespace s21

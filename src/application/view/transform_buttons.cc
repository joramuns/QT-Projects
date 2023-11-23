#include "transform_buttons.h"

// TEMP
#include <iostream>

namespace s21 {
TransformButtons::TransformButtons(const QChar labels[2][3])
    : QWidget(nullptr) {
  InitFields(labels);
  InitLayouts();
}

void TransformButtons::HandleTransform(double value, char axis) {
  std::cout << axis << " " << value << std::endl;
  emit EmitTransform(value, axis);
}

void TransformButtons::InitFields(const QChar labels[2][3]) {
  step_ = new QDoubleSpinBox;

  x_increase_ = new TButton('X' + labels[X_INCREASE_ROW][X_INCREASE_COL]);
  x_decrease_ = new TButton(labels[X_DECREASE_ROW][X_DECREASE_COL] + 'X');

  connect(x_increase_, &QPushButton::clicked, this,
          [=]() { this->HandleTransform(step_->value(), 'X'); });
  connect(x_decrease_, &QPushButton::clicked, this,
          [=]() { this->HandleTransform(-step_->value(), 'X'); });

  y_increase_ = new TButton('Y' + labels[Y_INCREASE_ROW][Y_INCREASE_COL]);
  y_decrease_ = new TButton('Y' + labels[Y_DECREASE_ROW][Y_DECREASE_COL]);

  connect(y_increase_, &QPushButton::clicked, this,
          [=]() { this->HandleTransform(step_->value(), 'Y'); });
  connect(y_decrease_, &QPushButton::clicked, this,
          [=]() { this->HandleTransform(-step_->value(), 'Y'); });

  z_increase_ = new TButton('Z' + labels[Z_INCREASE_ROW][Z_INCREASE_COL]);
  z_decrease_ = new TButton(labels[Z_DECREASE_ROW][Z_DECREASE_COL] + 'Z');

  connect(z_increase_, &QPushButton::clicked, this,
          [=]() { this->HandleTransform(step_->value(), 'Z'); });
  connect(z_decrease_, &QPushButton::clicked, this,
          [=]() { this->HandleTransform(-step_->value(), 'Z'); });
}

void TransformButtons::InitLayouts() {
  QVBoxLayout *layout = new QVBoxLayout();
  setLayout(layout);

  QHBoxLayout *h_layout_upper = new QHBoxLayout();
  QHBoxLayout *h_layout_lower = new QHBoxLayout();
  QFormLayout *form_layout = new QFormLayout();
  form_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

  h_layout_upper->addWidget(z_decrease_);
  h_layout_upper->addWidget(y_increase_);
  h_layout_upper->addWidget(z_increase_);

  h_layout_lower->addWidget(x_decrease_);
  h_layout_lower->addWidget(y_decrease_);
  h_layout_lower->addWidget(x_increase_);

  form_layout->addRow(new QLabel(tr("Step:")), step_);

  layout->addLayout(h_layout_upper);
  layout->addLayout(h_layout_lower);
  layout->addLayout(form_layout);
}

ScaleButtons::ScaleButtons() : QWidget(nullptr) {
  InitFields();
  InitLayouts();
}

void ScaleButtons::InitFields() {
  increase_ = new TButton("+");
  decrease_ = new TButton("-");

  step_ = new QDoubleSpinBox;
}

void ScaleButtons::InitLayouts() {
  QVBoxLayout *layout = new QVBoxLayout;
  setLayout(layout);

  QHBoxLayout *h_layout = new QHBoxLayout();
  QFormLayout *form_layout = new QFormLayout();
  form_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

  h_layout->addWidget(increase_);
  h_layout->addWidget(decrease_);

  form_layout->addRow(new QLabel(tr("Step:")), step_);

  layout->addLayout(h_layout);
  layout->addLayout(form_layout);
}

TButton::TButton(const QString &label) : QPushButton(label) {
  setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
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

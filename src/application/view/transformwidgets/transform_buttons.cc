#include "transform_buttons.h"

// TEMP
#include <iostream>

namespace s21 {
TransformButtons::TransformButtons(const QChar labels[2][3], int type) {
  InitFields(labels);
  ConnectFields(type);
  InitLayouts();
}

void TransformButtons::TransformSlot(double value, char axis, int type) {
  emit TransformSignal(value, axis, type);
}

void TransformButtons::InitFields(const QChar labels[2][3]) {
  step_ = new QDoubleSpinBox;

  x_increase_ = new TButton('X' + labels[X_INCREASE_ROW][X_INCREASE_COL]);
  x_decrease_ = new TButton(labels[X_DECREASE_ROW][X_DECREASE_COL] + 'X');

  y_increase_ = new TButton('Y' + labels[Y_INCREASE_ROW][Y_INCREASE_COL]);
  y_decrease_ = new TButton('Y' + labels[Y_DECREASE_ROW][Y_DECREASE_COL]);

  z_increase_ = new TButton('Z' + labels[Z_INCREASE_ROW][Z_INCREASE_COL]);
  z_decrease_ = new TButton(labels[Z_DECREASE_ROW][Z_DECREASE_COL] + 'Z');
}

void TransformButtons::ConnectFields(int type) {
  connect(x_increase_, &TButton::clicked, this, [=]() {
    TransformButtons::TransformSlot(-step_->value() * type, 'X', type);
  });
  connect(x_decrease_, &TButton::clicked, this, [=]() {
    TransformButtons::TransformSlot(step_->value() * type, 'X', type);
  });

  connect(y_increase_, &TButton::clicked, this, [=]() {
    TransformButtons::TransformSlot(-step_->value() * type, 'Y', type);
  });
  connect(y_decrease_, &TButton::clicked, this, [=]() {
    TransformButtons::TransformSlot(step_->value() * type, 'Y', type);
  });

  connect(z_increase_, &TButton::clicked, this, [=]() {
    TransformButtons::TransformSlot(-step_->value() * type, 'Z', type);
  });
  connect(z_decrease_, &TButton::clicked, this, [=]() {
    TransformButtons::TransformSlot(step_->value() * type, 'Z', type);
  });
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
  step_->setMinimum(0.1f);
  step_->setSingleStep(0.05f);

  layout->addLayout(h_layout_upper);
  layout->addLayout(h_layout_lower);
  layout->addLayout(form_layout);
}
}  // namespace s21

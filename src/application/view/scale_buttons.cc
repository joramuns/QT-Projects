#include "scale_buttons.h"

namespace s21 {
ScaleButtons::ScaleButtons() : QWidget(nullptr) {
  InitFields();
  ConnectFields();
  InitLayouts();
}

void ScaleButtons::HandleTransform(double value, char axis, int type) {
  emit EmitTransform(value, axis, type);
}

void ScaleButtons::InitFields() {
  increase_ = new TButton("+");
  decrease_ = new TButton("-");

  step_ = new QDoubleSpinBox;
}

void ScaleButtons::ConnectFields() {
  connect(increase_, &TButton::clicked, this,
          [=]() { ScaleButtons::HandleTransform(step_->value(), 'S', SCALE); });
  connect(decrease_, &TButton::clicked, this, [=]() {
    ScaleButtons::HandleTransform(-step_->value(), 'S', SCALE);
  });
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
}  // namespace s21

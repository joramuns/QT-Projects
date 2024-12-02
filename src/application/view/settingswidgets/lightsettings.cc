#include "lightsettings.h"

namespace s21 {
LightSettings::LightSettings(std::array<std::string, 3> labels,
                             float bound_value)
    : labels_(labels), bound_value_(bound_value) {
  layout_ = new QVBoxLayout();
  setLayout(layout_);
  InitFields();
  ConnectFields();
}

void LightSettings::SetDecimals(int prec) {
  for (int i = 0; i != 3; ++i) {
    inputs_[i]->setDecimals(prec);
  }
}

void LightSettings::InitFields() {
  for (int i = 0; i != 3; ++i) {
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    QLabel *label = new QLabel(QString::fromStdString(labels_[i]));
    inputs_[i] = new QDoubleSpinBox();
    inputs_[i]->setRange(-bound_value_, bound_value_);
    inputs_[i]->setValue(1.0);
    inputs_[i]->setSingleStep(0.1);
    inputs_[i]->setDecimals(1);
    hboxLayout->addWidget(label);
    hboxLayout->addWidget(inputs_[i]);
    layout_->addLayout(hboxLayout);
  }
}

void LightSettings::ConnectFields() {
  for (int i = 0; i != 3; ++i) {
    connect(inputs_[i], &QDoubleSpinBox::valueChanged, this,
            &LightSettings::PositionSlot);
  }
}

void LightSettings::PositionSlot() {
  std::array<double, 3> args;
  for (int i = 0; i != 3; ++i) {
    args[i] = inputs_[i]->value();
  }
  emit PositionSignal(args);
}
void PositionSignal(std::array<double, 3> args);

/* } */
}  // namespace s21

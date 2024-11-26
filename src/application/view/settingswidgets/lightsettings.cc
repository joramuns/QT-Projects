#include "lightsettings.h"

namespace s21 {
LightSettings::LightSettings() {
  layout_ = new QVBoxLayout();
  setLayout(layout_);
  InitFields();
  ConnectFields();
  InitLayouts();
}

void LightSettings::InitFields() {
  color_ = new QPushButton("Light color");
  CreateLabelButton("X position:", x_pos_);
  CreateLabelButton("Y position:", y_pos_);
  CreateLabelButton("Z position:", z_pos_);
}

void LightSettings::CreateLabelButton(QString text, QDoubleSpinBox *pos) {
  QHBoxLayout *hboxLayout = new QHBoxLayout();
  QLabel *label = new QLabel(text);
  pos = new QDoubleSpinBox();
  pos->setRange(-1.0, 1.0);
  pos->setValue(1.0);
  pos->setSingleStep(0.1);
  pos->setDecimals(1);
  hboxLayout->addWidget(label);
  hboxLayout->addWidget(pos);
  layout_->addLayout(hboxLayout);

}

void LightSettings::ConnectFields() {}

void LightSettings::InitLayouts() {
  layout_->addWidget(color_);
}
}  // namespace s21

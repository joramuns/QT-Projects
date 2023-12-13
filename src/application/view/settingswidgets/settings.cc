#include "settings.h"

namespace s21 {
ASettings::ASettings() {
  layout_ = new QVBoxLayout();
  setLayout(layout_);
}

void ASettings::ColorSlot() { emit ColorSignal(); }

void ASettings::ComboBoxSlot() {
  emit ComboBoxSignal(static_cast<QComboBox *>(sender())->currentText());
}

SceneSettings::SceneSettings() {
  InitFields();
  ConnectFields();
  InitLayouts();
}

void SceneSettings::InitFields() {
  color_ = new QPushButton("Color");
  type_ = new QComboBox();
}

void SceneSettings::ConnectFields() {
  connect(color_, &QPushButton::clicked, this, &SceneSettings::ColorSlot);
  connect(type_, &QComboBox::currentIndexChanged, this,
          &SceneSettings::ComboBoxSlot);
}

void SceneSettings::InitLayouts() {
  layout_->addWidget(color_);
  layout_->addWidget(type_);
}

void SceneSettings::SetComboBoxOptions(const QVector<QString> &labels) {
  for (const auto &item : labels) {
    type_->addItem(item);
  }
}

ModelSettings::ModelSettings() {
  InitFields();
  ConnectFields();
  InitLayouts();
}

void ModelSettings::SpinBoxSlot() {
  emit SpinBoxSignal(static_cast<QDoubleSpinBox *>(sender())->value());
}

void ModelSettings::InitFields() { size_ = new QDoubleSpinBox(); }

void ModelSettings::ConnectFields() {
  connect(size_, &QDoubleSpinBox::valueChanged, this,
          &ModelSettings::SpinBoxSlot);
}

void ModelSettings::InitLayouts() { layout_->addWidget(size_); }
}  // namespace s21

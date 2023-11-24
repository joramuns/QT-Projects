#include "settings.h"

namespace s21 {
ASettings::ASettings() {
  layout_ = new QVBoxLayout();
  setLayout(layout_);
}

SceneSettings::SceneSettings() {
  InitFields();
  InitLayouts();
}

void SceneSettings::InitFields() {
  color_ = new QPushButton("Color");
  type_ = new QComboBox();
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
  InitLayouts();
}

void ModelSettings::InitFields() { size_ = new QDoubleSpinBox(); }

void ModelSettings::InitLayouts() { layout_->addWidget(size_); }
}  // namespace s21

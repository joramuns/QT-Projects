#include "settings.h"

namespace s21 {
ASettings::ASettings() {
  layout_ = new QVBoxLayout();
  setLayout(layout_);
}

void ASettings::ColorSlot() { emit ColorSignal(); }

void ASettings::ComboBoxSlot() {
  emit ComboBoxSignal(static_cast<QComboBox *>(sender())->currentIndex());
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

void SceneSettings::SetComboBox(const int index) {
  type_->setCurrentIndex(index);
}

ExtraSceneSettings::ExtraSceneSettings() {
  InitFields();
  ConnectFields();
  InitLayouts();
}

void ExtraSceneSettings::InitFields() { wireframe_type_ = new QComboBox(); }

void ExtraSceneSettings::ConnectFields() {
  connect(wireframe_type_, &QComboBox::currentIndexChanged, this,
          &ExtraSceneSettings::ExtraComboBoxSlot);
}

void ExtraSceneSettings::InitLayouts() { layout_->addWidget(wireframe_type_); }

void ExtraSceneSettings::SetExtraComboBoxOptions(
    const QVector<QString> &labels) {
  for (const auto &item : labels) {
    wireframe_type_->addItem(item);
  }
}

void ExtraSceneSettings::SetExtraComboBox(const int index) {
  wireframe_type_->setCurrentIndex(index);
}

void ExtraSceneSettings::ExtraComboBoxSlot() {
  emit ExtraComboBoxSignal(static_cast<QComboBox *>(sender())->currentIndex());
}

ModelSettings::ModelSettings() {
  InitFields();
  ConnectFields();
  InitLayouts();
}

void ModelSettings::SpinBoxSlot() {
  emit SpinBoxSignal(static_cast<QDoubleSpinBox *>(sender())->value());
}

void ModelSettings::InitFields() {
  size_ = new QDoubleSpinBox();
  size_->setDecimals(1);
  size_->setSingleStep(0.1);
  size_->setMinimum(0.1);
  size_->setMaximum(30.0);
  size_->setValue(1.0);
}

void ModelSettings::ConnectFields() {
  connect(size_, &QDoubleSpinBox::valueChanged, this,
          &ModelSettings::SpinBoxSlot);
}

void ModelSettings::InitLayouts() { layout_->addWidget(size_); }

void ModelSettings::SetSpinBox(const double value) { size_->setValue(value); }
}  // namespace s21

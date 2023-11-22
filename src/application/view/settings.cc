#include "settings.h"

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

SettingsTab::SettingsTab() {
  scene_settings_ = new SceneSettings();
  scene_settings_->SetComboBoxOptions(
      QVector<QString>{"Central projection", "Parallel projection"});
  vertex_settings_ = new ModelSettings();
  vertex_settings_->SetComboBoxOptions(
      QVector<QString>{"None", "Round", "Square"});
  edge_settings_ = new ModelSettings();
  edge_settings_->SetComboBoxOptions(QVector<QString>{"Solid", "Dashed"});

  addTab(scene_settings_, "Common");
  addTab(vertex_settings_, "Vertex");
  addTab(edge_settings_, "Edge");
}

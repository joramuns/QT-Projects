#include "settingstab.h"

// TEMP
#include <iostream>

namespace s21 {
SettingsTab::SettingsTab() {
  scene_settings_ = new ExtraSceneSettings();
  scene_settings_->SetComboBoxOptions(
      QVector<QString>{"Parallel projection", "Central projection"});
  scene_settings_->SetExtraComboBoxOptions(
      QVector<QString>{"Wireframe", "Solid"});

  vertex_settings_ = new ModelSettings();
  vertex_settings_->SetComboBoxOptions(
      QVector<QString>{"None", "Round", "Square"});

  edge_settings_ = new ModelSettings();
  edge_settings_->SetComboBoxOptions(QVector<QString>{"Solid", "Dashed"});

  connect(scene_settings_, &SceneSettings::ColorSignal, this,
          &SettingsTab::SceneColorSlot);
  connect(vertex_settings_, &SceneSettings::ColorSignal, this,
          &SettingsTab::VertexColorSlot);
  connect(edge_settings_, &SceneSettings::ColorSignal, this,
          &SettingsTab::EdgeColorSlot);

  connect(scene_settings_, &SceneSettings::ComboBoxSignal, this,
          &SettingsTab::SceneOptionSlot);
  connect(scene_settings_, &ExtraSceneSettings::ExtraComboBoxSignal, this,
          &SettingsTab::ExtraSceneOptionSlot);
  connect(vertex_settings_, &SceneSettings::ComboBoxSignal, this,
          &SettingsTab::VertexOptionSlot);
  connect(edge_settings_, &SceneSettings::ComboBoxSignal, this,
          &SettingsTab::EdgeOptionSlot);

  connect(vertex_settings_, &ModelSettings::SpinBoxSignal, this,
          &SettingsTab::VertexSizeSlot);
  connect(edge_settings_, &ModelSettings::SpinBoxSignal, this,
          &SettingsTab::EdgeSizeSlot);

  addTab(scene_settings_, "Common");
  addTab(vertex_settings_, "Vertex");
  addTab(edge_settings_, "Edge");
}

void SettingsTab::SceneColorSlot() {
  QColor scene_color = QColorDialog::getColor(Qt::white, this);
  emit TabSceneColorSignal(scene_color);
}

void SettingsTab::VertexColorSlot() {
  std::cout << "Vertex color tab" << std::endl;
  QColor vertex_color = QColorDialog::getColor(Qt::white, this);
  QVector3D vertex_vcolor{vertex_color.redF(), vertex_color.greenF(), vertex_color.blueF()};
  emit TabVertexColorSignal(vertex_vcolor);
}

void SettingsTab::EdgeColorSlot() {
  QColor edge_color = QColorDialog::getColor(Qt::white, this);
  QVector3D edge_vcolor{edge_color.redF(), edge_color.greenF(), edge_color.blueF()};
  emit TabEdgeColorSignal(edge_vcolor);
}

void SettingsTab::SceneOptionSlot(int index) {
  emit TabSceneOptionSignal(index);
}

void SettingsTab::ExtraSceneOptionSlot(int index) {
  emit TabExtraSceneOptionSignal(index);
}

void SettingsTab::VertexOptionSlot(int index) {
  std::cout << "Vertex option " << index << std::endl;
  emit TabVertexOptionSignal(index);
}

void SettingsTab::EdgeOptionSlot(int index) {
  std::cout << "Edge option " << index << std::endl;
  emit TabEdgeOptionSignal(index);
}

void SettingsTab::VertexSizeSlot(double value) {
  std::cout << "Vertex size: " << value << std::endl;
  emit TabVertexSizeSignal(value);
}
void SettingsTab::EdgeSizeSlot(double value) {
  std::cout << "Edge size: " << value << std::endl;
  emit TabEdgeSizeSignal(value);
}
}  // namespace s21

#include "settingstab.h"

namespace s21 {
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
}  // namespace s21

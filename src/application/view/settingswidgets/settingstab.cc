#include "settingstab.h"

namespace s21 {
SettingsTab::SettingsTab() {
  InitFields();
  ReadSettings();
  ConnectFields();
  AddTab();
}

void SettingsTab::InitFields() {
  scene_settings_ = new ExtraSceneSettings();
  scene_settings_->SetComboBoxOptions(
      QVector<QString>{"Parallel projection", "Central projection"});
  scene_settings_->SetExtraComboBoxOptions(
      QVector<QString>{"Wireframe", "Flat shading", "Gouraud shading", "Phong shading"});

  vertex_settings_ = new ModelSettings();
  vertex_settings_->SetComboBoxOptions(
      QVector<QString>{"None", "Square", "Round"});

  edge_settings_ = new ModelSettings();
  edge_settings_->SetComboBoxOptions(QVector<QString>{"Solid", "Dashed"});

  light_pos_settings_ =
      new LightSettings({"X position", "Y position", "Z position"}, 1.0);
  light_col_settings_ = new LightSettings({"Red", "Green", "Blue"}, 255.0);
  light_col_settings_->SetDecimals(0);
}

void SettingsTab::ConnectFields() {
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

  connect(light_pos_settings_, &LightSettings::PositionSignal, this,
          &SettingsTab::TabLightPositionSignal);
  connect(light_col_settings_, &LightSettings::PositionSignal, this,
          &SettingsTab::TabLightColorSignal);
}

void SettingsTab::AddTab() {
  addTab(scene_settings_, "Common");
  addTab(vertex_settings_, "Vertex");
  addTab(edge_settings_, "Edge");
  addTab(light_pos_settings_, "Light position");
  addTab(light_col_settings_, "Light color");
}

void SettingsTab::ReadSettings() {
  SettingsSingleton &settings = SettingsSingleton::GetInstance();
  scene_settings_->SetComboBox(settings.GetProjectionType());
  scene_settings_->SetExtraComboBox(settings.GetPolygonType());
  vertex_settings_->SetComboBox(settings.GetVertexType());
  vertex_settings_->SetSpinBox(settings.GetVertexSize());
  edge_settings_->SetComboBox(settings.GetEdgeType());
  edge_settings_->SetSpinBox(settings.GetEdgeSize());
}

void SettingsTab::SceneColorSlot() {
  QColor scene_color = QColorDialog::getColor(Qt::white, this);
  emit TabSceneColorSignal(scene_color);
}

void SettingsTab::VertexColorSlot() {
  QColor vertex_color = QColorDialog::getColor(Qt::white, this);
  QVector3D vertex_vcolor{vertex_color.redF(), vertex_color.greenF(),
                          vertex_color.blueF()};
  emit TabVertexColorSignal(vertex_vcolor);
}

void SettingsTab::EdgeColorSlot() {
  QColor edge_color = QColorDialog::getColor(Qt::white, this);
  QVector3D edge_vcolor{edge_color.redF(), edge_color.greenF(),
                        edge_color.blueF()};
  emit TabEdgeColorSignal(edge_vcolor);
}

void SettingsTab::SceneOptionSlot(int index) {
  emit TabSceneOptionSignal(index);
}

void SettingsTab::ExtraSceneOptionSlot(int index) {
  emit TabExtraSceneOptionSignal(index);
}

void SettingsTab::VertexOptionSlot(int index) {
  emit TabVertexOptionSignal(index);
}

void SettingsTab::EdgeOptionSlot(int index) { emit TabEdgeOptionSignal(index); }

void SettingsTab::VertexSizeSlot(double value) {
  emit TabVertexSizeSignal(value);
}
void SettingsTab::EdgeSizeSlot(double value) { emit TabEdgeSizeSignal(value); }

void SettingsTab::LightColorSlot(std::array<double, 3> args) {
  emit TabLightColorSignal(args);
}
void SettingsTab::LightPositionSlot(std::array<double, 3> args) {
  emit TabLightPositionSignal(args);
}
}  // namespace s21

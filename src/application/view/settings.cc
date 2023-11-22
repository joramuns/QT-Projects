#include "settings.h"

CommonSettings::CommonSettings() {
  QVBoxLayout *layout = new QVBoxLayout();
  setLayout(layout);

  type_ = new QComboBox();
  type_->addItem("Parallel");
  type_->addItem("Central");

  color_ = new QPushButton("Vertex color");
  
  layout->addWidget(type_);
  layout->addWidget(color_);
}

VertexSettings::VertexSettings() {
  QVBoxLayout *layout = new QVBoxLayout();
  setLayout(layout);

  type_ = new QComboBox();
  type_->addItem("None");
  type_->addItem("Round");
  type_->addItem("Square");

  size_ = new QDoubleSpinBox();

  color_ = new QPushButton("Vertex color");

  layout->addWidget(type_);
  layout->addWidget(size_);
  layout->addWidget(color_);
}

EdgeSettings::EdgeSettings() {
  QVBoxLayout *layout = new QVBoxLayout();
  setLayout(layout);

  type_ = new QCheckBox("Dashed lines");

  size_ = new QDoubleSpinBox();

  color_ = new QPushButton("Vertex color");

  layout->addWidget(type_);
  layout->addWidget(size_);
  layout->addWidget(color_);
}

SettingsTab::SettingsTab() {
  common_settings_ = new CommonSettings();
  vertex_settings_ = new VertexSettings();
  edge_settings_ = new EdgeSettings();

  addTab(common_settings_, "Common");
  addTab(vertex_settings_, "Vertex");
  addTab(edge_settings_, "Edge");
}

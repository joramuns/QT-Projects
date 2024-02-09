#include "view.h"

#include <iostream>

namespace s21 {
  View::~View() { std::cout << "View dtor" << std::endl; }
View::View(GLWidget *context) : QWidget(nullptr) {
  main_layout_ = new QGridLayout(this);
  setWindowTitle("3D Viewer 2.0");
  /* setFixedSize(500, 500); */

  QGroupBox *menu_box = new QGroupBox("Menu");
  menu_box->setFixedWidth(330);
  QVBoxLayout *menu_layout = new QVBoxLayout(menu_box);
  TransformationTab *transformation_tab = new TransformationTab();
  connect(transformation_tab, &TransformationTab::TransformTabSignal, this,
          [=](double value, char axis, int type) {
            View::ViewTransformSlot(value, axis, type,
                                    list_widget_->currentRow());
          });

  SettingsTab *settings_tab = new SettingsTab();
  connect(settings_tab, &SettingsTab::TabSceneOptionSignal, this,
          &View::SceneOptionSlot);
  connect(settings_tab, &SettingsTab::TabExtraSceneOptionSignal, this,
          &View::ExtraSceneOptionSlot);
  connect(settings_tab, &SettingsTab::TabSceneColorSignal, this,
          &View::SceneColorSlot);
  connect(settings_tab, &SettingsTab::TabVertexColorSignal, this,
          &View::VertexColorSlot);
  connect(settings_tab, &SettingsTab::TabEdgeColorSignal, this,
          &View::EdgeColorSlot);

  connect(settings_tab, &SettingsTab::TabVertexOptionSignal, this,
          &View::VertexOptionSlot);
  connect(settings_tab, &SettingsTab::TabEdgeOptionSignal, this,
          &View::EdgeOptionSlot);

  connect(settings_tab, &SettingsTab::TabVertexSizeSignal, this,
          &View::VertexSizeSlot);
  connect(settings_tab, &SettingsTab::TabEdgeSizeSignal, this,
          &View::EdgeSizeSlot);

  AppManagement *app_management = new AppManagement("Main menu");
  connect(app_management, &AppManagement::AppOpenFileSignal, this,
          &View::OpenFileSlot);
  connect(app_management, &AppManagement::AppCloseFileSignal, this,
          &View::CloseFileSlot);

  menu_layout->addStretch();
  menu_layout->addWidget(transformation_tab);
  menu_layout->addStretch();
  menu_layout->addWidget(settings_tab);
  menu_layout->addStretch();
  menu_layout->addWidget(app_management);
  menu_layout->addStretch();

  QGroupBox *group_box = new QGroupBox();
  QVBoxLayout *group_layout = new QVBoxLayout(group_box);
  gl_widget_ = context;
  group_layout->addWidget(gl_widget_);

  QGroupBox *list_box = new QGroupBox();
  QHBoxLayout *list_layout = new QHBoxLayout(list_box);
  list_widget_ = new QListWidget();
  list_layout->addWidget(list_widget_);

  main_layout_->addWidget(menu_box, 0, 0, 1, 1);
  main_layout_->addWidget(group_box, 0, 1, 1, 6);
  main_layout_->addWidget(list_box, 1, 0, 1, 6);
}

void View::AddListWidgetItem(const QString filename) {
  new QListWidgetItem(filename, list_widget_);
}

void View::RemoveListWidgetItem(int model_number) {
  delete list_widget_->takeItem(model_number);
  list_widget_->removeItemWidget(list_widget_->takeItem(model_number));
}

/* Slots */

void View::ViewTransformSlot(double value, char axis, int type,
                             int model_number) {
  emit ViewTransformSignal(value, axis, type, model_number);
}

void View::OpenFileSlot(QString filename) { emit OpenFileSignal(filename); }

void View::CloseFileSlot() {
  if (list_widget_->currentRow() >= 0) {
    emit CloseFileSignal(list_widget_->currentRow());
  }
}

void View::SceneOptionSlot(int index) { emit SceneOptionSignal(index); }

void View::ExtraSceneOptionSlot(int index) {
  emit ExtraSceneOptionSignal(index);
}

void View::SceneColorSlot(QColor scene_color) {
  emit SceneColorSignal(scene_color);
}

void View::VertexColorSlot(QVector3D vertex_color) {
  emit VertexColorSignal(vertex_color);
}

void View::EdgeColorSlot(QVector3D edge_color) {
  emit EdgeColorSignal(edge_color);
}

void View::VertexOptionSlot(int index) { emit VertexOptionSignal(index); }

void View::EdgeOptionSlot(int index) { emit EdgeOptionSignal(index); }

void View::VertexSizeSlot(double value) { emit VertexSizeSignal(value); }

void View::EdgeSizeSlot(double value) { emit EdgeSizeSignal(value); }

}  // namespace s21

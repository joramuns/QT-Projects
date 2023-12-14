#include "view.h"

// TEMP
#include <iostream>

namespace s21 {
View::View() : QWidget(nullptr) {
  main_layout_ = new QGridLayout(this);
  setWindowTitle("3D Viewer 2.0");
  /* setFixedSize(500, 500); */

  QGroupBox *menu_box = new QGroupBox("Menu");
  menu_box->setFixedWidth(330);
  QVBoxLayout *menu_layout = new QVBoxLayout(menu_box);
  TransformationTab *transformation_tab = new TransformationTab();
  connect(transformation_tab, &TransformationTab::TransformTabSignal, this,
          &View::ViewTransformSlot);

  SettingsTab *settings_tab = new SettingsTab();
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
  gl_widget_ = new GLWidget();
  group_layout->addWidget(gl_widget_);

  QGroupBox *list_box = new QGroupBox();
  QHBoxLayout *list_layout = new QHBoxLayout(list_box);
  list_widget_ = new QListWidget();
  list_layout->addWidget(list_widget_);

  main_layout_->addWidget(menu_box, 0, 0, 1, 1);
  main_layout_->addWidget(group_box, 0, 1, 1, 6);
  main_layout_->addWidget(list_box, 1, 0, 1, 6);
}

void View::LoadModel(std::vector<GLfloat> vertices,
                     std::vector<GLuint> indices) {
  gl_widget_->LoadModel(vertices, indices);
}

void View::UnloadModel(int model_number) {
  gl_widget_->UnloadModel(model_number);
  list_widget_->removeItemWidget(list_widget_->takeItem(model_number));
}

void View::Rotate(double value, char axis) {
  gl_widget_->Rotate(value, axis);
  gl_widget_->update();
}

void View::Move(double value, char axis) {
  gl_widget_->Move(value, axis);
  gl_widget_->update();
}

void View::Scale(double value) {
  gl_widget_->Scale(value);
  gl_widget_->update();
}

void View::AddListWidgetItem(const QString filename) {
  new QListWidgetItem(filename, list_widget_);
}

void View::ViewTransformSlot(double value, char axis, int type) {
  emit ViewTransformSignal(value, axis, type);
}

void View::OpenFileSlot(QString filename) { emit OpenFileSignal(filename); }

void View::CloseFileSlot() {
  if (list_widget_->currentRow() >= 0) {
    emit CloseFileSignal(list_widget_->currentRow());
  }
}
}  // namespace s21

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
  connect(app_management, &AppManagement::AppOpenFileSignal, this, &View::OpenFileSlot);

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

  main_layout_->addWidget(menu_box, 0, 0, 1, 1);
  main_layout_->addWidget(group_box, 0, 1, 1, 6);
}

void View::ViewTransformSlot(double value, char axis, int type) {
  emit ViewTransformSignal(value, axis, type);
}

void View::OpenFileSlot() {
  emit OpenFileSignal();
}
}  // namespace s21

#include "view.h"

#include <QCheckBox>
#include <QComboBox>
#include <QTabWidget>
#include <QSizePolicy>
#include <iostream>

namespace s21 {
View::View() : QWidget(nullptr) {
  main_layout = new QGridLayout();
  setLayout(main_layout);
  setWindowTitle("3D Viewer 2.0");
  /* setFixedSize(500, 500); */

  QGroupBox *menu_box = new QGroupBox("Menu");
  menu_box->setFixedWidth(330);
  QVBoxLayout *menu_layout = new QVBoxLayout(menu_box);
  TransformationTab *transformation_tab = new TransformationTab();
  SettingsTab *settings_tab = new SettingsTab();
  AppManagement *app_management = new AppManagement("Main menu");
  menu_layout->addWidget(transformation_tab);
  menu_layout->addWidget(settings_tab);
  menu_layout->addWidget(app_management);

  QGroupBox *group_box = new QGroupBox();
  QVBoxLayout *group_layout = new QVBoxLayout(group_box);
  GLWidget *gl_widget = new GLWidget();
  group_layout->addWidget(gl_widget);

  /* main_layout->addWidget(transformation_tab, 0, 0); */
  /* main_layout->addWidget(settings_tab, 1, 0); */
  /* main_layout->addWidget(app_management, 2, 0); */
  /* main_layout->addWidget(gl_widget, 0, 1, 3, 3); */
  main_layout->addWidget(menu_box, 0, 0, 1, 1);
  main_layout->addWidget(group_box, 0, 1, 1, 6);
}
}  // namespace s21

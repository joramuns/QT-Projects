#include "view.h"

#include <iostream>
#include <QTabWidget>
#include <QComboBox>
#include <QCheckBox>

namespace s21 {
View::View() : QWidget(nullptr) {
  main_layout = new QGridLayout();
  setLayout(main_layout);
  setWindowTitle("3D Viewer 2.0");
  /* setFixedSize(500, 500); */

  TransformationTab *transformation_tab = new TransformationTab();

  SettingsTab *settings_tab = new SettingsTab();

  main_layout->addWidget(transformation_tab, 0, 0);
  main_layout->addWidget(settings_tab, 2, 0);
}
}  // namespace s21

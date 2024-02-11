#include "app_management.h"

// TEMP
#include <iostream>

namespace s21 {
AppManagement::AppManagement(const QString &label) : QGroupBox(label) {
  InitFields();
  ConnectFields();
  InitLayouts();
}

void AppManagement::AppOpenFileSlot() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Choose model file:"), "", tr("Files (*.obj)"));
  emit AppOpenFileSignal(filename);
}

void AppManagement::AppCloseFileSlot() {
  emit AppCloseFileSignal();
}

void AppManagement::InitFields() {
  open_button_ = new QPushButton("Open file");
  close_button_ = new QPushButton("Close file");
  shot_button_ = new QPushButton("Screenshot");
  cast_button_ = new QPushButton("Screencast");
}

void AppManagement::ConnectFields() {
  connect(open_button_, &QPushButton::clicked, this,
          &AppManagement::AppOpenFileSlot);
  connect(close_button_, &QPushButton::clicked, this,
          &AppManagement::AppCloseFileSlot);
}

void AppManagement::InitLayouts() {
  QVBoxLayout *layout = new QVBoxLayout(this);

  layout->addWidget(open_button_);
  layout->addWidget(close_button_);
  layout->addWidget(shot_button_);
  layout->addWidget(cast_button_);
}
}  // namespace s21

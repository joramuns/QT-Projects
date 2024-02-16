#include "app_management.h"

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

void AppManagement::AppCloseFileSlot() { emit AppCloseFileSignal(); }

void AppManagement::AppScreenshotSlot() {
  QString filename = QFileDialog::getSaveFileName(
      this, "СКРИНШОТАНУТЬ?", "", "Images (*.bmp *.png *.jpeg)");
  if (filename.isEmpty()) {
    QMessageBox::critical(0, "Error", "File can not be created!");
  } else {
    emit AppScreenshotSignal(filename);
  }
}

void AppManagement::AppGifSlot() {
  QString filename = QFileDialog::getSaveFileName(
      this, "СКРИНШОТАНУТЬ?", "", "Images (*.bmp *.png *.jpeg)");
  if (filename.isEmpty()) {
    QMessageBox::critical(0, "Error", "File can not be created!");
  } else {
    emit AppGifSignal(filename);
  }
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
  connect(shot_button_, &QPushButton::clicked, this,
          &AppManagement::AppScreenshotSlot);
  connect(cast_button_, &QPushButton::clicked, this,
          &AppManagement::AppGifSlot);
}

void AppManagement::InitLayouts() {
  QVBoxLayout *layout = new QVBoxLayout(this);

  layout->addWidget(open_button_);
  layout->addWidget(close_button_);
  layout->addWidget(shot_button_);
  layout->addWidget(cast_button_);
}
}  // namespace s21

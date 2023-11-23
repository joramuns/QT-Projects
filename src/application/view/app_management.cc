#include "app_management.h"

namespace s21 {
AppManagement::AppManagement(const QString &label) : QGroupBox(label) {
  InitFields();
  InitLayouts();
}

void AppManagement::InitFields() {
  open_button_ = new QPushButton("Open file");
  shot_button_ = new QPushButton("Screenshot");
  cast_button_ = new QPushButton("Screencast");
}

void AppManagement::InitLayouts() {
  QVBoxLayout *layout = new QVBoxLayout(this);

  layout->addWidget(open_button_);
  layout->addWidget(shot_button_);
  layout->addWidget(cast_button_);
}
}  // namespace s21

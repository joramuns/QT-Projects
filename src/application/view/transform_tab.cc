#include "transform_tab.h"

// TEMP
#include <iostream>

namespace s21 {
TransformationTab::TransformationTab() {
  InitFields();
  ConnectFields();
}

void TransformationTab::HandleTransform(double value, char axis, int type) {
  std::cout << (type ? "Move " : "Rotate ") << "tab: " << axis << " " << value
            << " " << std::endl;
  emit EmitTransform(value, axis, type);
}

void TransformationTab::InitFields() {
  const QChar rotate_labels[2][3] = {
      {QChar(0x000027F2), QChar(0x000027F3), QChar(0x000027F3)},
      {QChar(0x000027F2), QChar(0x000027F2), QChar(0x000027F3)}};
  const QChar move_labels[2][3] = {
      {QChar(0x00002357), QChar(0x00002191), QChar(0x00002350)},
      {QChar(0x00002190), QChar(0x00002193), QChar(0x00002192)}};

  rotate_buttons_ = new TransformButtons(rotate_labels, ROTATE);
  move_buttons_ = new TransformButtons(move_labels, MOVE);
  scale_buttons_ = new ScaleButtons();

  addTab(rotate_buttons_, "Rotation");
  addTab(move_buttons_, "Movement");
  addTab(scale_buttons_, "Scaling");
}

void TransformationTab::ConnectFields() {
  connect(rotate_buttons_, &TransformButtons::EmitTransform, this,
          &TransformationTab::HandleTransform);
  connect(move_buttons_, &TransformButtons::EmitTransform, this,
          &TransformationTab::HandleTransform);
}
}  // namespace s21

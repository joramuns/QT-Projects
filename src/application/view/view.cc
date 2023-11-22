#include "view.h"

#include <iostream>

/* test->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum); */
namespace s21 {
View::View() : QWidget(nullptr) {
  main_layout = new QGridLayout();
  setLayout(main_layout);
  setWindowTitle("3D Viewer 2.0");
  setFixedSize(500, 500);

  const QChar rotate_labels[2][3] = {
      {QChar(0x000027F2), QChar(0x000027F3), QChar(0x000027F3)},
      {QChar(0x000027F2), QChar(0x000027F2), QChar(0x000027F3)}};
  TransformButtons *rotate_buttons = new TransformButtons(rotate_labels);

  const QChar move_labels[2][3] = {
      {QChar(0x00002357), QChar(0x00002191), QChar(0x00002350)},
      {QChar(0x00002190), QChar(0x00002193), QChar(0x00002192)}};
  TransformButtons *move_buttons = new TransformButtons(move_labels);

  ScaleButtons *scale_buttons = new ScaleButtons();

  main_layout->addWidget(rotate_buttons, 0, 0);
  main_layout->addWidget(move_buttons, 1, 0);
  main_layout->addWidget(scale_buttons, 2, 0);
}
}  // namespace s21

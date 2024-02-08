#include "transform_class.h"

// TEMP
#include <iostream>

namespace s21 {
Axes::Axes(double init) : x_(init), y_(init), z_(init) {}

void Axes::Change(double value, char axis) {
  std::cout << "Rotate glwidget " << x_ << " " << y_ << " " << z_ << " " << axis
            << std::endl;
  if (axis == 'X') {
    x_ += static_cast<GLfloat>(value);
  } else if (axis == 'Y') {
    y_ += static_cast<GLfloat>(value);
  } else if (axis == 'Z') {
    z_ += static_cast<GLfloat>(value);
  } else if (axis == 'A') {
    x_ = y_ = z_ += value;
  }
}

QVector3D Axes::GetChangeVector() { return QVector3D{x_, y_, z_}; }
} // namespace s21

#include "controller.h"

// TEMP
#include <iostream>

namespace s21 {
Controller::Controller(View *v) : view_(v) {
  connect(view_, &View::ViewTransformSignal, this,
          &Controller::ControllerTransformSlot);

  connect(view_, &View::OpenFileSignal, this,
          &Controller::ControllerOpenFileSlot);
}

void Controller::ControllerTransformSlot(double value, char axis, int type) {
  std::cout << (type ? axis == 'S' ? "Scale " : "Move " : "Rotate ")
            << "tab: " << axis << " " << value << " " << std::endl;
  if (type == ROTATE) {
    view_->Rotate(value, axis);
  } else if (type == MOVE) {
    view_->Move(value, axis);
  } else if (type == SCALE) {
    view_->Scale(value);
  }
}

void Controller::ControllerOpenFileSlot(QString filename) {
  std::cout << "Open file " << filename.toStdString() << std::endl;
  std::vector<GLfloat> vertices{
      0.0, 0.0, 0.0,  //
      0.0, 0.0, 0.5,  //
      0.0, 0.5, 0.0,  //
      0.0, 0.5, 0.5,  //
      0.5, 0.0, 0.0,  //
      0.5, 0.0, 0.5,  //
      0.5, 0.5, 0.0,  //
      0.5, 0.5, 0.5   //
  };
  std::vector<GLuint> indices{
      0, 6, 4,  //
      0, 2, 6,  //
      0, 3, 2,  //
      0, 1, 3,  //
      2, 7, 6,  //
      2, 3, 7,  //
      4, 6, 7,  //
      4, 7, 5,  //
      0, 4, 5,  //
      0, 5, 1,  //
      1, 5, 7,  //
      1, 7, 3,  //
  };
  std::vector<GLfloat> vertices1{
      0.5f,  0.5f,  0.0f,  // Верхний правый угол
      0.5f,  -0.5f, 0.0f,  // Нижний правый угол
      -0.5f, -0.5f, 0.0f,  // Нижний левый угол
      -0.5f, 0.5f,  0.0f   // Верхний левый угол
  };
  std::vector<GLuint> indices1{0, 1, 3};
  if (kek == 0) {
    view_->LoadModel(vertices, indices);
    ++kek;
  } else if (kek == 1) {
    view_->LoadModel(vertices1, indices1);
    ++kek;
  }
}
}  // namespace s21

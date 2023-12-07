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
}

void Controller::ControllerOpenFileSlot() {
  std::cout << "Open file" << std::endl;
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
  ShaderProgram test_program(vertices, indices);
  view_->Render(test_program.GetProgram(), test_program.GetVAO());
}
}  // namespace s21

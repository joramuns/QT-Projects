#include "controller.h"

// TEMP
#include <iostream>

namespace s21 {
Controller::Controller(View *v) : view_(v) {
  connect(view_, &View::ViewTransformSignal, this,
          &Controller::ControllerTransformSlot);
}

void Controller::ControllerTransformSlot(double value, char axis, int type) {
  std::cout << (type ? axis == 'S' ? "Scale " : "Move " : "Rotate ")
            << "tab: " << axis << " " << value << " " << std::endl;
}
}  // namespace s21

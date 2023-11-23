#include "controller.h"

// TEMP
#include <iostream>

namespace s21 {
Controller::Controller(View *v) : view_(v) {
  connect(view_, &View::EmitTransform, this, &Controller::HandleTransform);
}

void Controller::HandleTransform(double value, char axis, int type) {
  std::cout << (type ? "Move " : "Rotate ") << "tab: " << axis << " " << value
            << " " << std::endl;
}
}  // namespace s21

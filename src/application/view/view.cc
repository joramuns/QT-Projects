#include "view.h"

#include <iostream>

namespace s21 {
View::View() : QMainWindow(nullptr) {
  setFixedSize(500, 500);

  std::cout << "aaaaa" << std::endl;

  QPushButton *test = new QPushButton(this);
  test->setGeometry(QRect(10, 10, 100, 100));
}
}  // namespace s21

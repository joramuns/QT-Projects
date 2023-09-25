#include "main.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  s21::Model cmodel;
  s21::CalcWindow cview;
  s21::Controller controller(&cview, &cmodel);
  cview.show();
#if defined(__APPLE__)
  std::locale loc("en_US.UTF-8");
  std::locale::global(loc);
#elif defined(__linux__)
  std::locale loc("en_US.utf8");
  std::locale::global(loc);
#endif
  return app.exec();
}

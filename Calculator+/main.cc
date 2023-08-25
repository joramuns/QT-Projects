#include "main.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  s21::Model cmodel;
  s21::CalcWindow cview(&cmodel);
  s21::Controller controller(&cview, &cmodel);
  cview.show();
  return app.exec();
}

#include "main.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  /* s21::Model m; */
  s21::View v;
  /* s21::Controller(v, m); */
  v.show();

  return app.exec();
}

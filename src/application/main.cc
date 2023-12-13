#include "main.h"

#include <QSurfaceFormat>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QSurfaceFormat format;
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);
  app.setApplicationName("3D Viewer");
  app.setApplicationVersion("2.0");
  /* s21::Model m; */
  s21::Fasade f;
  s21::View v;
  /* s21::Controller(v, m); */
  s21::Controller c(&v, &f);
  v.show();

  return app.exec();
}


#include <QApplication>

#include "mainwidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWidget h;
  h.show();
  int end = a.exec();
  if (h.m_paint_widget->view.sorted_array != nullptr) {
    free(h.m_paint_widget->view.sorted_array);
  }
  return end;
}

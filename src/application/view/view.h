#ifndef VIEW_H_
#define VIEW_H_

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "app_management.h"
#include "opengl/glwidget.h"
#include "settings.h"
#include "transform_tab.h"

namespace s21 {
class View final : public QWidget {
  Q_OBJECT

 public:
  View();

 private slots:
  void ViewTransformSlot(double value, char axis, int type);

 signals:
  void ViewTransformSignal(double value, char axis, int type);

 private:
  QGridLayout *main_layout;
  int test = 1;
};
}  // namespace s21

#endif  // VIEW_H_

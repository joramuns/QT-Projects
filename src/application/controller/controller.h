#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QWidget>

#include "../model/shaderprogram.h"
#include "../view/view.h"

namespace s21 {
class Controller final : public QObject {
  Q_OBJECT

 public:
  explicit Controller(View *v);

 private slots:
  void ControllerTransformSlot(double value, char axis, int type);
  void ControllerOpenFileSlot();

 private:
  View *view_;
  int kek = 0;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_

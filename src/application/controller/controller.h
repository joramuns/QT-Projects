#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QWidget>

#include "../model/shaderprogram.h"
#include "../view/view.h"
#include "../../model/fasade/fasade.h"

namespace s21 {
class Controller final : public QObject {
  Q_OBJECT

 public:
  Controller(View *v, Fasade *f);

 private slots:
  void ControllerTransformSlot(double value, char axis, int type, int model_number);
  void ControllerOpenFileSlot(QString filename);
  void ControllerCloseFileSlot(int model_number);

 private:
  View *view_;
  Fasade *fasade_;
  int kek = 0;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_

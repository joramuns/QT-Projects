#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QWidget>

#include "../model/fasade/fasade.h"
#include "../model/shaderprogram.h"
#include "../view/view.h"

namespace s21 {
class Controller final : public QObject {
  Q_OBJECT

 public:
  Controller(View *v, Fasade *f);

 private slots:
  void ControllerTransformSlot(double value, char axis, int type,
                               int model_number);
  void ControllerOpenFileSlot(QString filename);
  void ControllerCloseFileSlot(int model_number);
  void ControllerSceneOptionSlot(int index);
  void ControllerExtraSceneOptionSlot(int index);
  void ControllerSceneColor(QColor scene_color);
  void ControllerEdgeColor(QVector3D edge_color);

 private:
  View *view_;
  Fasade *fasade_;
  int kek = 0;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_

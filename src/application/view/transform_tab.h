#ifndef VIEW_TRANSFORM_TAB_H_
#define VIEW_TRANSFORM_TAB_H_

#include <QTabWidget>

#include "scale_buttons.h"
#include "transform_buttons.h"

namespace s21 {
class TransformationTab final : public QTabWidget {
  Q_OBJECT

 public:
  TransformationTab();

 private slots:
  void HandleTransform(double value, char axis, int type);

 signals:
  void EmitTransform(double value, char axis, int type);

 private:
  void InitFields();
  void ConnectFields();

 private:
  TransformButtons *rotate_buttons_;
  TransformButtons *move_buttons_;
  ScaleButtons *scale_buttons_;
};
}  // namespace s21

#endif  // VIEW_TRANSFORM_TAB_H_

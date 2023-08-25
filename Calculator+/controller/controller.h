#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QLabel>
#include <QObject>

#include "../model/model.h"
#include "../view/calcwindow.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT

 public:
  Controller() = delete;
  Controller(CalcWindow *cview, Model *cmodel);
  Controller(const Controller &other) = delete;
  Controller(Controller &&other) = delete;
  Controller &operator=(const Controller &other) = delete;
  Controller &operator=(Controller &&other) = delete;

 public slots:
  void ClearButton() noexcept;
  void NumButton() noexcept;
  void OperButton() noexcept;
  void EvalButton() noexcept;

 private:
  void Render() const noexcept;
  /* MVC */
  CalcWindow *view_;
  Model *model_;
};
}  // namespace s21
#endif  // CONTROLLER_CONTROLLER_H_

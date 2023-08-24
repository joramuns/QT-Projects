#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QObject>
#include "../model/model.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT

 public:
  Controller() = default;
  Controller(const Controller &other) = delete;
  Controller(Controller &&other) = delete;
  Controller &operator=(const Controller &other) = delete;
  Controller &operator=(Controller &&other) = delete;

 /* public slots: */
  void ClearSlot2();

 private:
  Model calcmodel_;
};
}  // namespace s21
#endif  // CONTROLLER_CONTROLLER_H_

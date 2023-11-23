#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QWidget>

#include "../view/view.h"

namespace s21 {
  class Controller final : public QObject {
    Q_OBJECT

   public:
    explicit Controller(View *v);

   private slots:
    void HandleTransform(double value, char axis, int type);

   private:
    View *view_;
  };
}

#endif  // CONTROLLER_CONTROLLER_H_

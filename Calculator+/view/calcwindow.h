#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "../model/model.h"

namespace s21 {
class CalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CalcWindow(Model *cmodel);
  ~CalcWindow();

 private slots:
  void HandleNumButton(int a);
  void ClearSlot();

 public:
  std::array<QPushButton *, 10> num_buttons_;
  std::array<QPushButton *, 5> operator_buttons_;
  QPushButton *clear_;
  QLabel *display_;
  /* MVC */
  s21::Model *model_;
};
}  // namespace s21
#endif  // MAINWINDOW_H

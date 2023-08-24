#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include "../controller/controller.h"

namespace s21 {
class CalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CalcWindow(QWidget *parent = nullptr);
  ~CalcWindow();
 private slots:
  void HandleNumButton(int a);
  void ClearSlot();

 private:
  std::array<QPushButton *, 10> num_buttons_;
  std::array<QPushButton *, 5> operator_buttons_;
  QPushButton *clear_;
  QLabel *display_;
  Controller controller_;
};
}  // namespace s21
#endif  // MAINWINDOW_H

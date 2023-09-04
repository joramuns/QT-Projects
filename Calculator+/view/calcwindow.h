#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QRegularExpressionValidator>
#define QCUSTOMPLOT_USE_LIBRARY
#include "../model/model.h"
#include "../qcustomplot/qcustomplot.h"
#include "operatorbutton.h"

namespace s21 {
class CalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CalcWindow(Model *cmodel);
  ~CalcWindow();

 public:
  std::array<QPushButton *, 13> num_buttons_;
  std::array<OperatorButton *, 17> operator_buttons_;
  std::array<QLineEdit *, 5> input_lines_;
  QRegularExpressionValidator *regex_validator_;
  QPushButton *clear_;
  QPushButton *eval_;
  QPushButton *make_plot_;
  QLabel *display_;
  QCustomPlot *plot_;
  QListWidget *results_display_;
  /* MVC */
  s21::Model *model_;

 private:
  enum OperatorType {
    kAddition = 1,
    kSubtraction,
    kMultiplication = 10,
    kDivision,
    kModulus,
    kPower,
    kSin = 1000,
    kCos,
    kTan,
    kAsin,
    kAcos,
    kAtan,
    kSqrt,
    kLn,
    kLog,
    kBracketOpen = 10000,
    kBracketClose
  };
};
}  // namespace s21
#endif  // MAINWINDOW_H

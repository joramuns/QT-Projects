#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <memory>
#define QCUSTOMPLOT_USE_LIBRARY
#include "../model/model.h"
#include "../libs/qcustomplot/qcustomplot.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "operatorbutton.h"

namespace s21 {
class CalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CalcWindow(Model *cmodel);

  /* Accessors */
  const std::string GetDomains(const int number) const noexcept;

  /* Mutators */
  void SetExpression(const std::string &expression) noexcept;
  void AddResults(const std::string &result) noexcept;
  void DrawPlot(const QVector<double> &x, const QVector<double> &y,
                const std::vector<double> &borders);

 public:
  std::array<QPushButton *, 13> num_buttons_;
  std::array<OperatorButton *, 17> operator_buttons_;
  QPushButton *clear_;
  QPushButton *eval_;
  QPushButton *make_plot_;

  /* Bonus part */
  CreditWindow *credit_window_;
  DepositWindow *deposit_window_;

 private:
  void InitNumButtons();
  void InitOperButtons();
  void InitInputLines();
  void InitEvalButtons();
  void InitOutput();

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
  std::array<QLabel *, 5> input_labels_;
  std::array<QLineEdit *, 5> input_lines_;
  std::unique_ptr<QRegularExpressionValidator> regex_validator_;
  QCustomPlot *plot_;
  QLabel *display_;
  QListWidget *results_display_;
};

}  // namespace s21
#endif  // MAINWINDOW_H

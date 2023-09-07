#include "calcwindow.h"

namespace s21 {
CalcWindow::CalcWindow(Model *cmodel) : QMainWindow(nullptr), credit_window_(new CreditWindow()) {
  resize(950, 400);
  credit_window_->setAttribute(Qt::WA_DeleteOnClose, true);
  credit_window_->show();

  /* Num Buttons */
  InitNumButtons();

  /* Operators Buttons */
  InitOperButtons();

  /* Input lines */
  InitInputLines();

  /* Evaluate button */
  InitEvalButtons();

  /* Displays */
  InitOutput();
}

CalcWindow::~CalcWindow() {
  /* for (const auto &item : num_buttons_) delete item; */
  /* for (const auto &item : operator_buttons_) delete item; */
  /* for (const auto &item : input_lines_) delete item; */
  /* for (const auto &item : input_labels_) delete item; */
  delete regex_validator_;
  /* delete clear_; */
  /* delete eval_; */
  /* delete make_plot_; */
  /* delete display_; */
  /* delete results_display_; */
  /* delete plot_; */
}

void CalcWindow::DrawPlot(const QVector<double> &x, const QVector<double> &y,
                          const std::vector<double> &borders) {
  if (x.empty() && y.empty()) {
    plot_->legend->setVisible(true);
  } else {
    plot_->legend->setVisible(false);
  }
  plot_->xAxis->setRange(borders[0], borders[1]);
  plot_->yAxis->setRange(borders[2], borders[3]);
  plot_->graph(0)->setData(x, y);
  plot_->replot();
}

void CalcWindow::InitNumButtons() {
  int button_size = 50;
  QSize q_button_size{button_size, button_size};
  QPoint button_pos{0, 150};
  int offset_x = 0;
  int offset_y = 200;

  QVector<QString> num_buttons_labels = {"1", "2", "3", "4", "5", "6", "7",
                                         "8", "9", "0", ".", "e", "x"};
  for (int i = 12; i >= 0; --i) {
    if (i == 12) {
      button_pos.setX(300);
      button_pos.setY(250);
    } else {
      button_pos.setX(button_size * (i % 3) + offset_x);
      button_pos.setY(button_size * (i / 3) + offset_y);
    }

    num_buttons_[i] = new QPushButton(num_buttons_labels[i], this);
    num_buttons_[i]->setGeometry(QRect(button_pos, q_button_size));
  }
}

void CalcWindow::InitOperButtons() {
  QPoint button_pos{0, 150};
  int button_size = 50;
  QSize q_button_size{button_size, button_size};

  clear_ = new QPushButton("\u232B", this);
  clear_->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[0] =
      new OperatorButton(OperatorType::kModulus, "mod", this);
  button_pos.setX(150);
  button_pos.setY(150);
  operator_buttons_[0]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[1] =
      new OperatorButton(OperatorType::kDivision, "\u00F7", this);
  button_pos.setX(150);
  button_pos.setY(200);
  operator_buttons_[1]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[2] =
      new OperatorButton(OperatorType::kMultiplication, "\u00D7", this);
  button_pos.setX(150);
  button_pos.setY(250);
  operator_buttons_[2]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[3] =
      new OperatorButton(OperatorType::kSubtraction, "\u2212", this);
  button_pos.setX(150);
  button_pos.setY(300);
  operator_buttons_[3]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[4] =
      new OperatorButton(OperatorType::kAddition, "\u002B", this);
  button_pos.setX(150);
  button_pos.setY(350);
  operator_buttons_[4]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[5] = new OperatorButton(OperatorType::kSin, "sin", this);
  button_pos.setX(200);
  button_pos.setY(150);
  operator_buttons_[5]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[6] = new OperatorButton(OperatorType::kCos, "cos", this);
  button_pos.setX(200);
  button_pos.setY(200);
  operator_buttons_[6]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[7] = new OperatorButton(OperatorType::kTan, "tan", this);
  button_pos.setX(200);
  button_pos.setY(250);
  operator_buttons_[7]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[8] = new OperatorButton(OperatorType::kAsin, "asin", this);
  button_pos.setX(250);
  button_pos.setY(150);
  operator_buttons_[8]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[9] = new OperatorButton(OperatorType::kAcos, "acos", this);
  button_pos.setX(250);
  button_pos.setY(200);
  operator_buttons_[9]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[10] = new OperatorButton(OperatorType::kAtan, "atan", this);
  button_pos.setX(250);
  button_pos.setY(250);
  operator_buttons_[10]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[11] =
      new OperatorButton(OperatorType::kBracketOpen, "(", this);
  button_pos.setX(50);
  button_pos.setY(150);
  operator_buttons_[11]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[12] =
      new OperatorButton(OperatorType::kBracketClose, ")", this);
  button_pos.setX(100);
  button_pos.setY(150);
  operator_buttons_[12]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[13] = new OperatorButton(OperatorType::kPower, "^", this);
  button_pos.setX(200);
  button_pos.setY(300);
  operator_buttons_[13]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[14] = new OperatorButton(OperatorType::kSqrt, "sqrt", this);
  button_pos.setX(200);
  button_pos.setY(350);
  operator_buttons_[14]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[15] = new OperatorButton(OperatorType::kLn, "ln", this);
  button_pos.setX(300);
  button_pos.setY(150);
  operator_buttons_[15]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[16] = new OperatorButton(OperatorType::kLog, "log", this);
  button_pos.setX(300);
  button_pos.setY(200);
  operator_buttons_[16]->setGeometry(QRect(button_pos, q_button_size));
}

void CalcWindow::InitInputLines() {
  int button_size = 50;
  QSize q_button_size{button_size, button_size};
  QPoint button_pos{0, 150};

  regex_validator_ = new QRegularExpressionValidator(
      QRegularExpression("[-]?[0]+[.][0-9]+|[-]?[1-9]+[0-9]*[.][0-9]*"));
  QVector<QString> labels{"X", "X min", "X max", "Y min", "Y max"};

  for (int i = 0; i < 5; ++i) {
    input_labels_[i] = new QLabel(labels[i], this);
    button_pos.setX(350);
    button_pos.setY(i * 50 + 150);
    q_button_size.setWidth(50);
    input_labels_[i]->setGeometry(QRect(button_pos, q_button_size));
    input_labels_[i]->setAlignment(Qt::AlignCenter);

    input_lines_[i] = new QLineEdit(i % 2 == 0 ? "5" : "-5", this);
    button_pos.setX(400);
    button_pos.setY(i * 50 + 150);
    q_button_size.setWidth(150);
    input_lines_[i]->setGeometry(QRect(button_pos, q_button_size));
    std::locale loc("en_US.utf8");
    std::locale::global(loc);
    input_lines_[i]->setValidator(regex_validator_);
  }
}

void CalcWindow::InitEvalButtons() {
  int button_size = 50;
  QSize q_button_size{button_size, button_size};
  QPoint button_pos{0, 150};
  eval_ = new QPushButton("=", this);
  button_pos.setX(250);
  button_pos.setY(300);
  q_button_size.setWidth(50);
  q_button_size.setHeight(100);
  eval_->setGeometry(QRect(button_pos, q_button_size));
  eval_->setStyleSheet("background-color: #893101; font: white;");

  make_plot_ = new QPushButton("Graph", this);
  button_pos.setX(300);
  button_pos.setY(300);
  q_button_size.setWidth(50);
  q_button_size.setHeight(100);
  make_plot_->setGeometry(QRect(button_pos, q_button_size));
  make_plot_->setStyleSheet("background-color: #893101; font: white;");
}

void CalcWindow::InitOutput() {
  display_ = new QLabel(this);
  display_->setGeometry(QRect(QPoint(0, 100), QSize(550, 50)));
  results_display_ = new QListWidget(this);
  results_display_->setGeometry(QRect(QPoint(0, 0), QSize(550, 100)));

  plot_ = new QCustomPlot(this);
  plot_->setBackground(QBrush(QColor("#333333")));
  plot_->setGeometry(QRect(QPoint(550, 0), QSize(400, 400)));
  plot_->addGraph();
  plot_->graph(0)->setLineStyle(QCPGraph::lsNone);
  QCPScatterStyle scatter_style =
      QCPScatterStyle(QCPScatterStyle::ssDisc, Qt::red, 3.0);
  plot_->graph(0)->setScatterStyle(scatter_style);
  plot_->graph(0)->setName("malfunction");

  QColor dot_lines_color("#787878");
  QColor solid_lines_color("#999999");
  plot_->xAxis->setLabel("x");
  plot_->xAxis->setTickLabelColor(solid_lines_color);
  plot_->xAxis->setLabelColor(solid_lines_color);
  plot_->xAxis->grid()->setPen(QPen(dot_lines_color, 1, Qt::DotLine));
  plot_->xAxis->grid()->setZeroLinePen(
      QPen(solid_lines_color, 1, Qt::SolidLine));

  plot_->yAxis->setLabel("y");
  plot_->yAxis->setTickLabelColor(solid_lines_color);
  plot_->yAxis->setLabelColor(solid_lines_color);
  plot_->yAxis->grid()->setPen(QPen(dot_lines_color, 1, Qt::DotLine));
  plot_->yAxis->grid()->setZeroLinePen(
      QPen(solid_lines_color, 1, Qt::SolidLine));
}

}  // namespace s21

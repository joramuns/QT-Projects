#include "calcwindow.h"

namespace s21 {
CalcWindow::CalcWindow(Model *cmodel) : QMainWindow(nullptr), model_(cmodel) {
  resize(500, 320);
  int button_size = 50;
  QSize q_button_size{button_size, button_size};
  QPoint button_pos{0, 0};

  int offset_x = 0;
  int offset_y = 50;

  /* Top level buttons */
  clear_ = new QPushButton("\u232B", this);
  clear_->setGeometry(QRect(button_pos, q_button_size));

  /* Num Buttons */
  for (int i = 11; i >= 0; --i) {
    button_pos.setX(button_size * (i % 3) + offset_x);
    button_pos.setY(button_size * (i / 3) + offset_y);

    QPushButton *new_button;
    if (i < 9) {
      new_button = new QPushButton(QString::number(i + 1), this);
    } else if (i == 9) {
      new_button = new QPushButton("0", this);
    } else if (i == 10) {
      new_button = new QPushButton(".", this);
    } else {
      new_button = new QPushButton("e", this);
    }

    new_button->setGeometry(QRect(button_pos, q_button_size));
    num_buttons_[i] = new_button;
  }

  /* Operators Buttons */
  operator_buttons_[0] =
      new OperatorButton(OperatorType::kModulus, "mod", this);
  button_pos.setX(150);
  button_pos.setY(0);
  operator_buttons_[0]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[1] =
      new OperatorButton(OperatorType::kDivision, "\u00F7", this);
  button_pos.setX(150);
  button_pos.setY(50);
  operator_buttons_[1]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[2] =
      new OperatorButton(OperatorType::kMultiplication, "\u00D7", this);
  button_pos.setX(150);
  button_pos.setY(100);
  operator_buttons_[2]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[3] =
      new OperatorButton(OperatorType::kSubtraction, "\u2212", this);
  button_pos.setX(150);
  button_pos.setY(150);
  operator_buttons_[3]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[4] =
      new OperatorButton(OperatorType::kAddition, "\u002B", this);
  button_pos.setX(150);
  button_pos.setY(200);
  operator_buttons_[4]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[5] = new OperatorButton(OperatorType::kSin, "sin", this);
  button_pos.setX(200);
  button_pos.setY(0);
  operator_buttons_[5]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[6] = new OperatorButton(OperatorType::kCos, "cos", this);
  button_pos.setX(200);
  button_pos.setY(50);
  operator_buttons_[6]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[7] = new OperatorButton(OperatorType::kTan, "tan", this);
  button_pos.setX(200);
  button_pos.setY(100);
  operator_buttons_[7]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[8] = new OperatorButton(OperatorType::kAsin, "asin", this);
  button_pos.setX(250);
  button_pos.setY(0);
  operator_buttons_[8]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[9] = new OperatorButton(OperatorType::kAcos, "acos", this);
  button_pos.setX(250);
  button_pos.setY(50);
  operator_buttons_[9]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[10] = new OperatorButton(OperatorType::kAtan, "atan", this);
  button_pos.setX(250);
  button_pos.setY(100);
  operator_buttons_[10]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[11] =
      new OperatorButton(OperatorType::kBracketOpen, "(", this);
  button_pos.setX(50);
  button_pos.setY(0);
  operator_buttons_[11]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[12] =
      new OperatorButton(OperatorType::kBracketClose, ")", this);
  button_pos.setX(100);
  button_pos.setY(0);
  operator_buttons_[12]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[13] = new OperatorButton(OperatorType::kPower, "^", this);
  button_pos.setX(200);
  button_pos.setY(150);
  operator_buttons_[13]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[14] = new OperatorButton(OperatorType::kSqrt, "sqrt", this);
  button_pos.setX(200);
  button_pos.setY(200);
  operator_buttons_[14]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[15] = new OperatorButton(OperatorType::kLn, "ln", this);
  button_pos.setX(300);
  button_pos.setY(0);
  operator_buttons_[15]->setGeometry(QRect(button_pos, q_button_size));

  operator_buttons_[16] = new OperatorButton(OperatorType::kLog, "log", this);
  button_pos.setX(300);
  button_pos.setY(50);
  operator_buttons_[16]->setGeometry(QRect(button_pos, q_button_size));

  /* Evaluate button */
  eval_ = new QPushButton("=", this);
  button_pos.setX(250);
  button_pos.setY(150);
  q_button_size.setHeight(100);
  eval_->setGeometry(QRect(button_pos, q_button_size));
  eval_->setStyleSheet("background-color: #893101; font: white;");

  /* Displays */
  display_ = new QLabel(this);
  display_->setGeometry(QRect(QPoint(0, 250), QSize(350, 50)));
  results_display_ = new QListWidget(this);
  results_display_->setGeometry(QRect(QPoint(0, 300), QSize(350, 100)));
}

CalcWindow::~CalcWindow() {
  for (const auto &item : num_buttons_) delete item;
  for (const auto &item : operator_buttons_) delete item;
  delete clear_;
  delete eval_;
  delete display_;
  delete results_display_;
}

void CalcWindow::HandleNumButton(int a) {
  // change the text
  display_->setText(display_->text() + QString::number(a + 1));
}

void CalcWindow::ClearSlot() { display_->setText(""); }

}  // namespace s21

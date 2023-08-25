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
  for (int i = 9; i >= 0; --i) {
    button_pos.setX(button_size * (i % 3) + offset_x);
    button_pos.setY(button_size * (i / 3) + offset_y);

    QPushButton *new_button =
        new QPushButton(QString::number(i < 9 ? (i + 1) : 0), this);
    new_button->setGeometry(QRect(button_pos, q_button_size));
    /* connect(new_button, &QPushButton::released, &controller_, */
    /*         [=]() { controller_.NumButton(i); }); */
    num_buttons_[i] = new_button;
  }

  /* Operators Buttons */
  operator_buttons_[0] = new QPushButton("mod", this);
  button_pos.setX(150);
  button_pos.setY(0);
  operator_buttons_[0]->setGeometry(QRect(button_pos, q_button_size));
  operator_buttons_[1] = new QPushButton("\u00F7", this);
  button_pos.setX(150);
  button_pos.setY(50);
  operator_buttons_[1]->setGeometry(QRect(button_pos, q_button_size));
  operator_buttons_[2] = new QPushButton("\u00D7", this);
  button_pos.setX(150);
  button_pos.setY(100);
  operator_buttons_[2]->setGeometry(QRect(button_pos, q_button_size));
  operator_buttons_[3] = new QPushButton("\u2212", this);
  button_pos.setX(150);
  button_pos.setY(150);
  operator_buttons_[3]->setGeometry(QRect(button_pos, q_button_size));
  operator_buttons_[4] = new QPushButton("\u002B", this);
  button_pos.setX(150);
  button_pos.setY(200);
  operator_buttons_[4]->setGeometry(QRect(button_pos, q_button_size));

  /* Display */
  display_ = new QLabel(this);
  display_->setGeometry(QRect(QPoint(0, 250), QSize(150, 50)));
}

CalcWindow::~CalcWindow() {
  for (const auto &item : num_buttons_) delete item;
  for (const auto &item : operator_buttons_) delete item;
  delete clear_;
  delete display_;
}

void CalcWindow::HandleNumButton(int a) {
  // change the text
  display_->setText(display_->text() + QString::number(a + 1));
}

void CalcWindow::ClearSlot() { display_->setText(""); }

}  // namespace s21

#include "creditwindow.h"

#include <iostream>

namespace s21 {
CreditWindow::CreditWindow() {
  setAttribute(Qt::WA_DeleteOnClose, true);
  resize(400, 400);
  setWindowTitle("Credit calculator");

  QVBoxLayout *main_layout = new QVBoxLayout;

  QGroupBox *input_group_box_ = AddInputGroupBox();
  QGroupBox *output_group_box_ = AddOutputGroupBox();
  eval_credit_ = new QPushButton("Credit me!");

  main_layout->addWidget(input_group_box_);
  main_layout->addWidget(output_group_box_);
  main_layout->addWidget(eval_credit_);
  setLayout(main_layout);
}

CreditWindow::~CreditWindow() {}

QGroupBox *CreditWindow::AddInputGroupBox() {
  QGroupBox *input_group_box_ = new QGroupBox(tr("Input data"));

  credit_amount_ = new QLineEdit;
  credit_term_ = new QSpinBox;
  credit_interest_ = new QLineEdit;
  credit_type_ = new QComboBox;

  credit_type_->addItem("annuity");
  credit_type_->addItem("differentiated");

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Total credit amount:")), credit_amount_);
  layout->addRow(new QLabel(tr("Term:")), credit_term_);
  layout->addRow(new QLabel(tr("Interest rate:")), credit_interest_);
  layout->addRow(new QLabel(tr("Type of credit:")), credit_type_);
  input_group_box_->setLayout(layout);

  return input_group_box_;
}

QGroupBox *CreditWindow::AddOutputGroupBox() {
  QGroupBox *output_group_box_ = new QGroupBox(tr("Output data"));

  payment_monthly_ = new QListWidget;
  payment_over_ = new QLineEdit;
  payment_total_ = new QLineEdit;

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Monthly payments:")), payment_monthly_);
  layout->addRow(new QLabel(tr("Overpayment:")), payment_over_);
  layout->addRow(new QLabel(tr("Total payment:")), payment_total_);
  output_group_box_->setLayout(layout);

  return output_group_box_;
}
}  // namespace s21

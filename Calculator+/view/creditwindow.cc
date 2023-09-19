#include "creditwindow.h"

#include <iostream>

namespace s21 {
CreditWindow::CreditWindow() {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setAttribute(Qt::WA_QuitOnClose, false);
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

void CreditWindow::OutputData(double over_payment, double total_payment,
                              std::vector<double> monthly_payments) {
  QString string_over_payment = QString::number(over_payment, 'd', 2);
  payment_over_->setText(string_over_payment);

  QString string_total_payment = QString::number(total_payment, 'd', 2);
  payment_total_->setText(string_total_payment);

  for (const auto &item : monthly_payments) {
    QString string_payment = QString::number(item, 'd', 3);
    string_payment.chop(1);
    payment_monthly_->addItem(string_payment);
  }

  payment_monthly_->scrollToBottom();
}

QGroupBox *CreditWindow::AddInputGroupBox() {
  QGroupBox *input_group_box = new QGroupBox(tr("Input data"));

  credit_amount_ = new QDoubleSpinBox;
  credit_amount_->setMinimum(0.01);
  credit_amount_->setMaximum(std::numeric_limits<double>::max());
  credit_term_ = new QDoubleSpinBox;
  credit_term_->setMinimum(1);
  credit_term_->setMaximum(std::numeric_limits<double>::max());
  credit_term_->setDecimals(0);
  credit_interest_ = new QDoubleSpinBox;
  credit_interest_->setMinimum(0);
  credit_interest_->setMaximum(std::numeric_limits<double>::max());

  credit_type_ = new QComboBox;
  credit_type_->addItem("annuity");
  credit_type_->addItem("differentiated");

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Total credit amount:")), credit_amount_);
  layout->addRow(new QLabel(tr("Term:")), credit_term_);
  layout->addRow(new QLabel(tr("Interest rate:")), credit_interest_);
  layout->addRow(new QLabel(tr("Type of credit:")), credit_type_);
  input_group_box->setLayout(layout);

  return input_group_box;
}

QGroupBox *CreditWindow::AddOutputGroupBox() {
  QGroupBox *output_group_box = new QGroupBox(tr("Output data"));

  payment_monthly_ = new QListWidget;
  payment_over_ = new QLineEdit;
  payment_total_ = new QLineEdit;

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Monthly payments:")), payment_monthly_);
  layout->addRow(new QLabel(tr("Overpayment:")), payment_over_);
  layout->addRow(new QLabel(tr("Total payment:")), payment_total_);
  output_group_box->setLayout(layout);

  return output_group_box;
}
}  // namespace s21

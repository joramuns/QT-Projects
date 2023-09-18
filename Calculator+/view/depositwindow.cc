#include "depositwindow.h"

namespace s21 {
DepositWindow::DepositWindow() {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setAttribute(Qt::WA_QuitOnClose, false);
  resize(400, 400);
  setWindowTitle("Deposit calculator");

  QVBoxLayout *main_layout = new QVBoxLayout;

  QGroupBox *input_group_box = AddInputGroupBox();
  QGroupBox *output_group_box = AddOutputGroupBox();
  eval_deposit_ = new QPushButton("Deposit me!", this);

  main_layout->addWidget(input_group_box);
  main_layout->addWidget(output_group_box);
  main_layout->addWidget(eval_deposit_);
  setLayout(main_layout);
}

DepositWindow::~DepositWindow(){};

double DepositWindow::GetReplenishmentDay() {
  return replenishment_day_->value();
}

double DepositWindow::GetReplenishmentAmount() {
  return replenishment_amount_->value();
}

double DepositWindow::GetWithdrawalDay() {
  return withdrawal_day_->value();
}

double DepositWindow::GetWithdrawalAmount() {
  return withdrawal_amount_->value();
}

void DepositWindow::AddReplenishment(const QString &replenishment) {
  replenishments_list_->addItem(replenishment);
}

void DepositWindow::ClearReplenishment() {
  replenishments_list_->clear();
}

void DepositWindow::AddWithdrawal(const QString &withdrawal) {
  withdrawals_list_->addItem(withdrawal);
}

void DepositWindow::ClearWithdrawal() {
  withdrawals_list_->clear();
}

QGroupBox *DepositWindow::AddInputGroupBox() {
  QGroupBox *input_group_box = new QGroupBox(tr("Input data"));

  deposit_amount_ = new QDoubleSpinBox;
  deposit_amount_->setMinimum(0.01);
  deposit_amount_->setMaximum(std::numeric_limits<double>::max());

  deposit_term_ = new QDoubleSpinBox;
  deposit_term_->setMinimum(1);
  deposit_term_->setMaximum(std::numeric_limits<double>::max());
  deposit_term_->setDecimals(0);

  deposit_interest_ = new QDoubleSpinBox;
  deposit_interest_->setMinimum(0);
  deposit_interest_->setMaximum(std::numeric_limits<double>::max());

  deposit_periodicity_ = new QComboBox;
  deposit_periodicity_->addItem("monthly");
  deposit_periodicity_->addItem("quarterly");
  deposit_periodicity_->addItem("annualy");

  capitalization_ = new QCheckBox;

  replenishments_list_ = new QListWidget;

  replenishment_day_ = new QDoubleSpinBox;
  replenishment_day_->setDecimals(0);
  replenishment_day_->setMinimum(1);
  replenishment_day_->setMaximum(std::numeric_limits<double>::max());

  replenishment_amount_ = new QDoubleSpinBox;
  replenishment_amount_->setMinimum(0.01);
  replenishment_amount_->setMaximum(std::numeric_limits<double>::max());

  add_replenishment_ = new QPushButton("+");
  remove_replenishment_ = new QPushButton("-");

  withdrawals_list_ = new QListWidget;

  withdrawal_day_ = new QDoubleSpinBox;
  withdrawal_day_->setDecimals(0);
  withdrawal_day_->setMinimum(1);
  withdrawal_day_->setMaximum(std::numeric_limits<double>::max());

  withdrawal_amount_ = new QDoubleSpinBox;
  withdrawal_amount_->setMinimum(0.01);
  withdrawal_amount_->setMaximum(std::numeric_limits<double>::max());

  add_withdrawal_ = new QPushButton("+");
  remove_withdrawal_ = new QPushButton("-");

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Amount:")), deposit_amount_);
  layout->addRow(new QLabel(tr("Term:")), deposit_term_);
  layout->addRow(new QLabel(tr("Interest rate:")), deposit_interest_);
  layout->addRow(new QLabel(tr("Periodicity of payments:")),
                 deposit_periodicity_);
  layout->addRow(new QLabel(tr("Capitalization of interest:")),
                 capitalization_);
  layout->addRow(new QLabel(tr("Replenishments:")), replenishments_list_);
  layout->addRow(new QLabel(tr("Day:")), replenishment_day_);
  layout->addRow(new QLabel(tr("Amount:")), replenishment_amount_);
  layout->addRow(add_replenishment_, remove_replenishment_);
  layout->addRow(new QLabel(tr("Withdrawals:")), withdrawals_list_);
  layout->addRow(new QLabel(tr("Day:")), withdrawal_day_);
  layout->addRow(new QLabel(tr("Amount:")), withdrawal_amount_);
  layout->addRow(add_withdrawal_, remove_withdrawal_);
  input_group_box->setLayout(layout);

  return input_group_box;
}

QGroupBox *DepositWindow::AddOutputGroupBox() {
  QGroupBox *output_group_box = new QGroupBox(tr("Output data"));

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Accrued interest:")), new QLineEdit);
  layout->addRow(new QLabel(tr("Tax amount:")), new QLineEdit);
  layout->addRow(new QLabel(tr("Deposit amount:")), new QLineEdit);
  output_group_box->setLayout(layout);

  return output_group_box;
}
}  // namespace s21

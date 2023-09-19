#include "depositwindow.h"

namespace s21 {
DepositWindow::DepositWindow() {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setAttribute(Qt::WA_QuitOnClose, false);
  setFixedSize(400, 900);
  setWindowTitle("Deposit calculator");

  QVBoxLayout *main_layout = new QVBoxLayout;

  QGroupBox *input_group_box = AddInputGroupBox();
  QGroupBox *input_extra_box = AddExtraGroupBox();
  QGroupBox *output_group_box = AddOutputGroupBox();
  eval_deposit_ = new QPushButton("Deposit me!", this);

  main_layout->addWidget(input_group_box);
  main_layout->addWidget(input_extra_box);
  main_layout->addWidget(output_group_box);
  main_layout->addWidget(eval_deposit_);
  setLayout(main_layout);
}

DepositWindow::~DepositWindow(){};

double DepositWindow::GetDepositAmount() const noexcept {
  return deposit_amount_->value();
}
double DepositWindow::GetDepositTerm() const noexcept {
  return deposit_term_->value();
}
double DepositWindow::GetDepositRate() const noexcept {
  return deposit_interest_->value();
}

double DepositWindow::GetDepositTaxRate() const noexcept {
  return deposit_tax_rate_->value();
}

/* QComboBox *deposit_periodicity_; */
/* QCheckBox *capitalization_; */

double DepositWindow::GetReplenishmentDay() const noexcept {
  return replenishment_day_->value();
}

double DepositWindow::GetReplenishmentAmount() const noexcept {
  return replenishment_amount_->value();
}

int DepositWindow::GetCurrentReplenishment() const noexcept {
  return replenishments_list_->currentRow();
}

double DepositWindow::GetWithdrawalDay() const noexcept {
  return withdrawal_day_->value();
}

double DepositWindow::GetWithdrawalAmount() const noexcept {
  return withdrawal_amount_->value();
}

int DepositWindow::GetCurrentWithdrawal() const noexcept {
  return withdrawals_list_->currentRow();
}

void DepositWindow::AddReplenishment(const QString &replenishment) {
  replenishments_list_->addItem(replenishment);
}

void DepositWindow::ClearReplenishment() { replenishments_list_->clear(); }

void DepositWindow::AddWithdrawal(const QString &withdrawal) {
  withdrawals_list_->addItem(withdrawal);
}

void DepositWindow::ClearWithdrawal() { withdrawals_list_->clear(); }

void DepositWindow::ScrollLists() noexcept {
  replenishments_list_->scrollToBottom();
  withdrawals_list_->scrollToBottom();
}

QGroupBox *DepositWindow::AddInputGroupBox() {
  QGroupBox *input_group_box = new QGroupBox(tr("Input data"));

  deposit_amount_ = new QDoubleSpinBox;
  deposit_amount_->setMinimum(0.01);
  deposit_amount_->setMaximum(std::numeric_limits<double>::max());

  deposit_term_ = new QDoubleSpinBox;
  deposit_term_->setMinimum(1.0);
  deposit_term_->setMaximum(std::numeric_limits<double>::max());
  deposit_term_->setDecimals(0.0);

  deposit_interest_ = new QDoubleSpinBox;
  deposit_interest_->setMinimum(0.0);
  deposit_interest_->setMaximum(std::numeric_limits<double>::max());

  deposit_tax_rate_ = new QDoubleSpinBox;
  deposit_tax_rate_->setMinimum(0.0);
  deposit_tax_rate_->setMaximum(100.0);

  deposit_periodicity_ = new QComboBox;
  deposit_periodicity_->addItem("monthly");
  deposit_periodicity_->addItem("quarterly");
  deposit_periodicity_->addItem("annualy");

  capitalization_ = new QCheckBox;

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Amount:")), deposit_amount_);
  layout->addRow(new QLabel(tr("Term:")), deposit_term_);
  layout->addRow(new QLabel(tr("Interest rate:")), deposit_interest_);
  layout->addRow(new QLabel(tr("Tax rate:")), deposit_tax_rate_);
  layout->addRow(new QLabel(tr("Periodicity of payments:")),
                 deposit_periodicity_);
  layout->addRow(new QLabel(tr("Capitalization of interest:")),
                 capitalization_);
  input_group_box->setLayout(layout);

  return input_group_box;
}

QGroupBox *DepositWindow::AddExtraGroupBox() {
  QGroupBox *input_extra_box = new QGroupBox(tr("Account movement"));

  replenishments_list_ = new QListWidget;

  replenishment_day_ = new QDoubleSpinBox;
  replenishment_day_->setDecimals(0.0);
  replenishment_day_->setMinimum(1.0);
  replenishment_day_->setMaximum(std::numeric_limits<double>::max());

  replenishment_amount_ = new QDoubleSpinBox;
  replenishment_amount_->setMinimum(0.01);
  replenishment_amount_->setMaximum(std::numeric_limits<double>::max());

  add_replenishment_ = new QPushButton("+");
  remove_replenishment_ = new QPushButton("-");

  withdrawals_list_ = new QListWidget;

  withdrawal_day_ = new QDoubleSpinBox;
  withdrawal_day_->setDecimals(0.0);
  withdrawal_day_->setMinimum(1.0);
  withdrawal_day_->setMaximum(std::numeric_limits<double>::max());

  withdrawal_amount_ = new QDoubleSpinBox;
  withdrawal_amount_->setMinimum(0.01);
  withdrawal_amount_->setMaximum(std::numeric_limits<double>::max());

  add_withdrawal_ = new QPushButton("+");
  remove_withdrawal_ = new QPushButton("-");

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Replenishments:")), replenishments_list_);
  layout->addRow(new QLabel(tr("Day:")), replenishment_day_);
  layout->addRow(new QLabel(tr("Amount:")), replenishment_amount_);
  layout->addRow(add_replenishment_, remove_replenishment_);
  layout->addRow(new QLabel(tr("Withdrawals:")), withdrawals_list_);
  layout->addRow(new QLabel(tr("Day:")), withdrawal_day_);
  layout->addRow(new QLabel(tr("Amount:")), withdrawal_amount_);
  layout->addRow(add_withdrawal_, remove_withdrawal_);
  input_extra_box->setLayout(layout);

  return input_extra_box;
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

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

/* Accessors */
const double DepositWindow::GetDepositAmount() const noexcept {
  return deposit_amount_->value();
}
const int DepositWindow::GetDepositTerm() const noexcept {
  return static_cast<int>(deposit_term_->value());
}
const double DepositWindow::GetDepositRate() const noexcept {
  return deposit_interest_->value();
}

const double DepositWindow::GetDepositTaxRate() const noexcept {
  return deposit_tax_rate_->value() / 100.0;
}

const int DepositWindow::GetPeriodicity() const noexcept {
  int periodicity = 0;
  int selection_number = deposit_periodicity_->currentIndex();

  if (selection_number == 0) {
    periodicity = kMonth;
  } else if (selection_number == 1) {
    periodicity = kQuarter;
  } else if (selection_number == 2) {
    periodicity = kYear;
  }

  return periodicity;
}

const bool DepositWindow::GetCapitalization() const noexcept {
  return capitalization_->isChecked();
}

const double DepositWindow::GetReplenishmentDay() const noexcept {
  return replenishment_day_->value();
}

const double DepositWindow::GetReplenishmentAmount() const noexcept {
  return replenishment_amount_->value();
}

const int DepositWindow::GetCurrentReplenishment() const noexcept {
  return replenishments_list_->currentRow();
}

const double DepositWindow::GetWithdrawalDay() const noexcept {
  return withdrawal_day_->value();
}

const double DepositWindow::GetWithdrawalAmount() const noexcept {
  return withdrawal_amount_->value();
}

const int DepositWindow::GetCurrentWithdrawal() const noexcept {
  return withdrawals_list_->currentRow();
}

/* Mutators */
void DepositWindow::AddReplenishment(const std::pair<double, double> &item) {
  QString replenishment_line = "[" + QString::number(item.first) +
                               "] Added: " + QString::number(item.second);
  replenishments_list_->addItem(replenishment_line);
}

void DepositWindow::ClearReplenishment() { replenishments_list_->clear(); }

void DepositWindow::AddWithdrawal(const std::pair<double, double> &item) {
  QString withdrawal_line = "[" + QString::number(item.first) +
                            "] Withdrawn: " + QString::number(item.second);
  withdrawals_list_->addItem(withdrawal_line);
}

void DepositWindow::ClearWithdrawal() { withdrawals_list_->clear(); }

void DepositWindow::ScrollLists() noexcept {
  replenishments_list_->scrollToBottom();
  withdrawals_list_->scrollToBottom();
}

void DepositWindow::AddPayoff(const double payoff) {
  payoffs_list_->addItem(QString::number(payoff, 'd', 2));
}

void DepositWindow::ClearPayoff() noexcept { payoffs_list_->clear(); }

void DepositWindow::SetTotalProfit(const double profit) noexcept {
  total_profit_->setText(QString::number(profit, 'd', 2));
}

void DepositWindow::SetTaxAmount(const double tax) noexcept {
  tax_amount_->setText(QString::number(tax, 'd', 2));
}

void DepositWindow::SetEndAmount(const double amount) noexcept {
  deposit_end_amount_->setText(QString::number(amount, 'd', 2));
}

/* Private deposit window functions */
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

  payoffs_list_ = new QListWidget;

  total_profit_ = new QLineEdit;

  tax_amount_ = new QLineEdit;

  deposit_end_amount_ = new QLineEdit;

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Accrued interest:")), payoffs_list_);
  layout->addRow(new QLabel(tr("Total interest:")), total_profit_);
  layout->addRow(new QLabel(tr("Tax amount:")), tax_amount_);
  layout->addRow(new QLabel(tr("Deposit amount:")), deposit_end_amount_);
  output_group_box->setLayout(layout);

  return output_group_box;
}

}  // namespace s21

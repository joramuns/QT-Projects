#include "controller.h"

#include <QDebug>
#include <QLocale>
#include <QPushButton>

namespace s21 {
Controller::Controller(CalcWindow *cview, Model *cmodel)
    : view_(cview), model_(cmodel) {
  /* Clear button signal */
  connect(view_->clear_, &QPushButton::released, this,
          &Controller::ClearButton);

  /* Num buttons signals */
  for (const auto &item : view_->num_buttons_) {
    connect(item, &QPushButton::released, this, &Controller::NumButton);
  }

  /* Operator buttons signals */
  for (const auto &item : view_->operator_buttons_) {
    connect(item, &QPushButton::released, this, &Controller::OperButton);
  }

  /* Evaluate and graph button signal */
  connect(view_->eval_, &QPushButton::released, this, &Controller::EvalButton);

  connect(view_->make_plot_, &QPushButton::released, this,
          &Controller::MakePlot);

  /* Credit calculator button */
  connect(view_->credit_window_->eval_credit_, &QPushButton::released, this,
          &Controller::CreditEvalButton);

  /* Deposit calculator buttons */
  connect(view_->deposit_window_->add_replenishment_, &QPushButton::released,
          this, &Controller::DepositAddReplenishment);

  connect(view_->deposit_window_->remove_replenishment_, &QPushButton::released,
          this, &Controller::DepositRemoveReplenishment);

  connect(view_->deposit_window_->add_withdrawal_, &QPushButton::released, this,
          &Controller::DepositAddWithdrawal);

  connect(view_->deposit_window_->remove_withdrawal_, &QPushButton::released,
          this, &Controller::DepositRemoveWithdrawal);

  connect(view_->deposit_window_->eval_deposit_, &QPushButton::released, this,
          &Controller::DepositEvalButton);
}

void Controller::ClearButton() noexcept {
  model_->ClearModel();
  Render();
}

void Controller::NumButton() noexcept {
  QString text_button = static_cast<QPushButton *>(sender())->text();
  char char_number = text_button[0].toLatin1();
  model_->AddElement(char_number);
  Render();
}

void Controller::OperButton() noexcept {
  OperatorButton *button = static_cast<OperatorButton *>(sender());
  int operator_type = button->GetType();
  model_->AddElement(operator_type);
  Render();
}

void Controller::EvalButton() noexcept {
  VariableSet();
  std::string result = model_->GetResult();
  view_->results_display_->addItem(QString::fromStdString(result));
  view_->results_display_->scrollToBottom();
}

void Controller::MakePlot() {
  std::vector<double> value_borders(4);
  for (int i = 0; i != 4; ++i) {
    auto input_string = view_->input_lines_[i + 1]->text().toStdString();
    if (input_string.empty()) {
      value_borders[i] = i % 2 == 0 ? 1.0 : -1.0;
    } else {
      value_borders[i] = std::stod(input_string);
    }
  }
  auto coords = model_->GetCoordinates(value_borders);
  QVector<double> x_qvector(coords.first.begin(), coords.first.end());
  QVector<double> y_qvector(coords.second.begin(), coords.second.end());
  view_->DrawPlot(x_qvector, y_qvector, value_borders);
}

void Controller::VariableSet() noexcept {
  QString input_value = view_->input_lines_[0]->text();
  if (!input_value.isEmpty()) {
    std::string std_input_value = input_value.toStdString();
    model_->SetVariables(std_input_value);
  }
}

/* Credit calc */

void Controller::CreditEvalButton() noexcept {
  SetCreditData();
  model_->credit_model_.Calculate();
  RenderCredit();
}

/* Deposit calc */

void Controller::DepositAddReplenishment() noexcept {
  DepositWindow *deposit_window = view_->deposit_window_;
  double max_day = deposit_window->GetDepositTerm();
  double day = deposit_window->GetReplenishmentDay();
  if (day <= max_day) {
    double amount = deposit_window->GetReplenishmentAmount();
    model_->deposit_model_.AddReplenishment(day, amount);
    RenderReplenishment();
  }
}

void Controller::DepositRemoveReplenishment() noexcept {
  int rep_row = view_->deposit_window_->GetCurrentReplenishment();
  if (rep_row >= 0) {
    model_->deposit_model_.RemoveReplenishment(rep_row);
    RenderReplenishment();
  }
}

void Controller::DepositAddWithdrawal() noexcept {
  DepositWindow *deposit_window = view_->deposit_window_;
  double max_day = deposit_window->GetDepositTerm();
  double day = deposit_window->GetWithdrawalDay();
  if (day <= max_day) {
    double amount = deposit_window->GetWithdrawalAmount();
    model_->deposit_model_.AddWithdrawal(day, amount);
    RenderWithdrawal();
  }
}

void Controller::DepositRemoveWithdrawal() noexcept {
  int rep_row = view_->deposit_window_->GetCurrentWithdrawal();
  if (rep_row >= 0) {
    model_->deposit_model_.RemoveWithdrawal(rep_row);
    RenderWithdrawal();
  }
}

void Controller::DepositEvalButton() noexcept {
  SetDepositData();
  model_->deposit_model_.EvaluateDeposit();
  RenderDeposit();
}

/* Private main calc function */
void Controller::Render() const noexcept {
  std::string infix_line = model_->GetInfixString();
  view_->display_->setText(QString::fromStdString(infix_line));
}

/* Private credit calc functions */
void Controller::SetCreditData() noexcept {
  CreditWindow *credit_window = view_->credit_window_;
  credit_window->payment_monthly_->clear();
  double set_amount = credit_window->credit_amount_->value();
  double set_term = credit_window->credit_term_->value();
  double set_rate = credit_window->credit_interest_->value();
  int set_type = credit_window->credit_type_->currentIndex();
  model_->credit_model_.SetData(set_amount, set_term, set_rate, set_type);
}

void Controller::RenderCredit() noexcept {
  double get_overpayment = model_->credit_model_.GetOverpayment();
  double get_total_payment = model_->credit_model_.GetTotalPayment();
  auto get_monthly_payments = model_->credit_model_.GetPayments();

  view_->credit_window_->OutputData(get_overpayment, get_total_payment,
                                    get_monthly_payments);
}

/* Private deposit calc function */
void Controller::RenderReplenishment() const noexcept {
  view_->deposit_window_->ClearReplenishment();
  QString replenishment_line;
  auto replenishment_list = model_->deposit_model_.GetReplenishmentList();
  for (const auto &item : replenishment_list) {
    replenishment_line = "[" + QString::number(item.first) +
                         "] Added: " + QString::number(item.second);
    view_->deposit_window_->AddReplenishment(replenishment_line);
    view_->deposit_window_->ScrollLists();
  }
}

void Controller::RenderWithdrawal() const noexcept {
  view_->deposit_window_->ClearWithdrawal();
  QString withdrawal_line;
  auto withdrawal_list = model_->deposit_model_.GetWithdrawalList();
  for (const auto &item : withdrawal_list) {
    withdrawal_line = "[" + QString::number(item.first) +
                      "] Withdrawn: " + QString::number(item.second);
    view_->deposit_window_->AddWithdrawal(withdrawal_line);
    view_->deposit_window_->ScrollLists();
  }
}

void Controller::SetDepositData() noexcept {
  DepositWindow *deposit_window = view_->deposit_window_;
  double set_amount = deposit_window->GetDepositAmount();
  double set_term = deposit_window->GetDepositTerm();
  double set_rate = deposit_window->GetDepositRate();
  model_->deposit_model_.SetDepositData(set_amount, set_term, set_rate);
  double set_periodicity = deposit_window->GetPeriodicity();
  bool set_capitalization = deposit_window->GetCapitalization();
  model_->deposit_model_.SetDepositType(set_periodicity, set_capitalization);
}

void Controller::RenderDeposit() const noexcept {
  view_->deposit_window_->ClearPayoff();
  QString payoff_line;
  auto payoffs_list = model_->deposit_model_.GetPayoffsList();
  for (const auto &item : payoffs_list) {
    payoff_line = QString::number(item);
    view_->deposit_window_->AddPayoff(payoff_line);
  }
}

}  // namespace s21

#include "controller.h"

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
  view_->AddResults(model_->GetResult());
}

void Controller::MakePlot() {
  std::vector<double> value_borders(4);
  for (int i = 0; i != 4; ++i) {
    auto input_string = view_->GetDomains(i + 1);
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
void Controller::VariableSet() noexcept {
  auto input_value = view_->GetDomains(0);
  if (!input_value.empty()) {
    model_->SetVariables(std::stod(input_value));
  }
}

void Controller::Render() const noexcept {
  view_->SetExpression(model_->GetInfixString());
}

/* Private credit calc functions */
void Controller::SetCreditData() noexcept {
  CreditWindow *credit_window = view_->credit_window_;
  credit_window->ClearPayments();
  double set_amount = credit_window->GetCreditAmount();
  double set_term = credit_window->GetCreditTerm();
  double set_rate = credit_window->GetCreditRate();
  int set_type = credit_window->GetCreditType();
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
  auto replenishment_list = model_->deposit_model_.GetReplenishmentList();
  for (const auto &item : replenishment_list) {
    view_->deposit_window_->AddReplenishment(item);
  }
  view_->deposit_window_->ScrollLists();
}

void Controller::RenderWithdrawal() const noexcept {
  view_->deposit_window_->ClearWithdrawal();
  auto withdrawal_list = model_->deposit_model_.GetWithdrawalList();
  for (const auto &item : withdrawal_list) {
    view_->deposit_window_->AddWithdrawal(item);
  }
  view_->deposit_window_->ScrollLists();
}

void Controller::SetDepositData() noexcept {
  DepositWindow *deposit_window = view_->deposit_window_;
  DepositCalc *deposit_model = &model_->deposit_model_;

  double set_amount = deposit_window->GetDepositAmount();
  double set_term = deposit_window->GetDepositTerm();
  double set_rate = deposit_window->GetDepositRate();
  deposit_model->SetDepositData(set_amount, set_term, set_rate);
  double set_tax = deposit_window->GetDepositTaxRate();
  int set_period = deposit_window->GetPeriodicity();
  bool set_capit = deposit_window->GetCapitalization();
  deposit_model->SetDepositType(set_tax, set_period, set_capit);
}

void Controller::RenderDeposit() const noexcept {
  DepositWindow *deposit_window = view_->deposit_window_;
  DepositCalc *deposit_model = &model_->deposit_model_;

  deposit_window->ClearPayoff();
  auto payoffs_list = deposit_model->GetPayoffsList();
  for (const auto &item : payoffs_list) {
    deposit_window->AddPayoff(item);
  }
  RenderWithdrawal();
  deposit_window->SetTotalProfit(deposit_model->GetTotalProfit());
  deposit_window->SetTaxAmount(deposit_model->GetTaxCharge());
  deposit_window->SetEndAmount(deposit_model->GetEndAmount());
}

}  // namespace s21

#ifndef VIEW_DEPOSITWINDOW_H_
#define VIEW_DEPOSITWINDOW_H_

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QWindow>

namespace s21 {
class DepositWindow : public QWidget {
  Q_OBJECT

 public:
  DepositWindow();
  ~DepositWindow();

  /* Accessors */
  const double GetDepositAmount() const noexcept;
  const int GetDepositTerm() const noexcept;
  const double GetDepositRate() const noexcept;
  const double GetDepositTaxRate() const noexcept;
  const int GetPeriodicity() const noexcept;
  const bool GetCapitalization() const noexcept;
  const double GetReplenishmentDay() const noexcept;
  const double GetReplenishmentAmount() const noexcept;
  const int GetCurrentReplenishment() const noexcept;
  const double GetWithdrawalDay() const noexcept;
  const double GetWithdrawalAmount() const noexcept;
  const int GetCurrentWithdrawal() const noexcept;

  /* Mutators */
  void AddReplenishment(const std::pair<double, double> &item);
  void ClearReplenishment();
  void AddWithdrawal(const std::pair<double, double> &item);
  void ClearWithdrawal();
  void ScrollLists() noexcept;
  void AddPayoff(const double payoff);
  void ClearPayoff() noexcept;
  void SetTotalProfit(const double profit) noexcept;
  void SetTaxAmount(const double tax) noexcept;
  void SetEndAmount(const double amount) noexcept;

 public:
  QPushButton *add_replenishment_;
  QPushButton *remove_replenishment_;

  QPushButton *add_withdrawal_;
  QPushButton *remove_withdrawal_;

  QPushButton *eval_deposit_;

 private:
  QGroupBox *AddInputGroupBox();
  QGroupBox *AddExtraGroupBox();
  QGroupBox *AddOutputGroupBox();

 private:
  enum Periodicity { kDay = 1, kMonth = 30, kQuarter = 90, kYear = 365 };
  /* Input block */
  QDoubleSpinBox *deposit_amount_;
  QDoubleSpinBox *deposit_term_;
  QDoubleSpinBox *deposit_interest_;
  QDoubleSpinBox *deposit_tax_rate_;
  QComboBox *deposit_periodicity_;
  QCheckBox *capitalization_;

  QListWidget *replenishments_list_;
  QDoubleSpinBox *replenishment_day_;
  QDoubleSpinBox *replenishment_amount_;

  QListWidget *withdrawals_list_;
  QDoubleSpinBox *withdrawal_day_;
  QDoubleSpinBox *withdrawal_amount_;

  /* Output block */
  QListWidget *payoffs_list_;
  QLineEdit *total_profit_;
  QLineEdit *tax_amount_;
  QLineEdit *deposit_end_amount_;
};
}  // namespace s21
#endif  // VIEW_DEPOSITWINDOW_H_

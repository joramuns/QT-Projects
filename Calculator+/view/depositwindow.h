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

  /* Getters */
  double GetDepositAmount() const noexcept;
  double GetDepositTerm() const noexcept;
  double GetDepositRate() const noexcept;
  /* QComboBox *deposit_periodicity_; */
  /* QCheckBox *capitalization_; */
  double GetReplenishmentDay() const noexcept;
  double GetReplenishmentAmount() const noexcept;
  double GetWithdrawalDay() const noexcept;
  double GetWithdrawalAmount() const noexcept;

  /* Mutators */
  void AddReplenishment(const QString &replenishment);
  void ClearReplenishment();
  void AddWithdrawal(const QString &withdrawal);
  void ClearWithdrawal();

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
  /* Input block */
  QDoubleSpinBox *deposit_amount_;
  QDoubleSpinBox *deposit_term_;
  QDoubleSpinBox *deposit_interest_;
  QComboBox *deposit_periodicity_;
  QCheckBox *capitalization_;

  QListWidget *replenishments_list_;
  QDoubleSpinBox *replenishment_day_;
  QDoubleSpinBox *replenishment_amount_;

  QListWidget *withdrawals_list_;
  QDoubleSpinBox *withdrawal_day_;
  QDoubleSpinBox *withdrawal_amount_;
};
}  // namespace s21
#endif  // VIEW_DEPOSITWINDOW_H_

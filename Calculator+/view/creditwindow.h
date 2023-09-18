#ifndef VIEW_CREDITWINDOW_H_
#define VIEW_CREDITWINDOW_H_

#include <QComboBox>
#include <QDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

namespace s21 {
class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  CreditWindow();
  ~CreditWindow();

  void OutputData(double over_payment, double total_payment,
                  std::vector<double> monthly_payments);

 private:
  QGroupBox *AddInputGroupBox();
  QGroupBox *AddOutputGroupBox();

 public:
  /* Input block */
  QDoubleSpinBox *credit_amount_;
  QDoubleSpinBox *credit_term_;
  QDoubleSpinBox *credit_interest_;
  QComboBox *credit_type_;
  /* Output block */
  QListWidget *payment_monthly_;
  QLineEdit *payment_over_;
  QLineEdit *payment_total_;
  /* Buttons block */
  QPushButton *eval_credit_;
};
}  // namespace s21
#endif  // VIEW_CREDITWINDOW_H_

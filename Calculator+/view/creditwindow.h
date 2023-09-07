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

 public:
  /* Input block */
  QLineEdit *credit_amount_;
  QDoubleSpinBox *credit_term_;
  QLineEdit *credit_interest_;
  QComboBox *credit_type_;
  /* Output block */
  QListWidget *payment_monthly_;
  QLineEdit *payment_over_;
  QLineEdit *payment_total_;
  /* Buttons block */
  QPushButton *eval_credit_;

 private:
  QGroupBox *AddInputGroupBox();
  QGroupBox *AddOutputGroupBox();
};
}  // namespace s21
#endif  // VIEW_CREDITWINDOW_H_

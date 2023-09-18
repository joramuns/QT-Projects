#ifndef VIEW_DEPOSITWINDOW_H_
#define VIEW_DEPOSITWINDOW_H_

#include <QDialog>
#include <QWindow>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QListWidget>
#include <QPushButton>

namespace s21 {
class DepositWindow : public QWidget {
  Q_OBJECT

 public:
  DepositWindow();
  ~DepositWindow();

 private:
  QGroupBox *AddInputGroupBox();
  QGroupBox *AddOutputGroupBox();
};
}  // namespace s21
#endif  // VIEW_DEPOSITWINDOW_H_

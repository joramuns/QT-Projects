#include "depositwindow.h"

namespace s21 {
DepositWindow::DepositWindow() {
  setAttribute(Qt::WA_DeleteOnClose, true);
  setAttribute(Qt::WA_QuitOnClose, false );
  resize(400, 400);
  setWindowTitle("Deposit calculator");

  QVBoxLayout *main_layout = new QVBoxLayout;

  QGroupBox *input_group_box = AddInputGroupBox();
  QGroupBox *output_group_box = AddOutputGroupBox();

  main_layout->addWidget(input_group_box);
  main_layout->addWidget(output_group_box);
  setLayout(main_layout);
}

DepositWindow::~DepositWindow(){};

QGroupBox *DepositWindow::AddInputGroupBox() {
  QGroupBox *input_group_box = new QGroupBox(tr("Input data"));

  QFormLayout *layout = new QFormLayout;
  layout->addRow(new QLabel(tr("Amount:")), new QDoubleSpinBox);
  layout->addRow(new QLabel(tr("Term:")), new QDoubleSpinBox);
  layout->addRow(new QLabel(tr("Interest rate:")), new QDoubleSpinBox);
  layout->addRow(new QLabel(tr("Periodicity of payments:")), new QComboBox);
  layout->addRow(new QLabel(tr("Capitalization of interest:")), new QCheckBox);
  layout->addRow(new QLabel(tr("Replenishments:")), new QListWidget);
  layout->addRow(new QLabel(tr("Day:")), new QDoubleSpinBox);
  layout->addRow(new QLabel(tr("Amount:")), new QDoubleSpinBox);
  layout->addRow(new QPushButton("+"), new QPushButton("-"));
  layout->addRow(new QLabel(tr("Withdrawals:")), new QListWidget);
  layout->addRow(new QLabel(tr("Day:")), new QDoubleSpinBox);
  layout->addRow(new QLabel(tr("Amount:")), new QDoubleSpinBox);
  layout->addRow(new QPushButton("+"), new QPushButton("-"));
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

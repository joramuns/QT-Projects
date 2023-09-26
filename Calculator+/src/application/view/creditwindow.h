/**
 * @file
 * @brief Заголовочный файл с описанием класса CreditWindow
 *
 * Данный класс является дополнительным классом view приложения калькулятор.
 * В нем содержатся поля ввода данных для расчета кредита, а также кнопка
 * расчета кредита и поля вывода платежей и переплаты по кредиту.
 */
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
/**
 * @brief Класс отображения дополнительного функционала приложения - кредитный
 * калькулятор.
 */
class CreditWindow : public QWidget {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса по умолчанию, инициализирует приватные поля
   */
  CreditWindow();

  /* Accessors */
  /**
   * @brief Функция, возвращающая значение поля ввода суммы кредита
   *
   * @return Сумма кредита
   */
  double GetCreditAmount() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода срока кредита
   *
   * @return Срок кредита
   */
  double GetCreditTerm() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода процентной ставки кредита
   *
   * @return Процентная ставка
   */
  double GetCreditRate() const noexcept;
  /**
   * @brief Функция, возвращающая тип кредита
   *
   * @return 1 - дифференцированный, 0 - аннуитетный
   */
  int GetCreditType() const noexcept;

  /* Mutators */
  /**
   * @brief Функция очистки поля вывода платежей
   */
  void ClearPayments() noexcept;
  /**
   * @brief Функция установки значений полей вывода
   *
   * @param over_payment Переплата по кредиту
   * @param total_payment Общий платеж по кредиту
   * @param monthly_payments Ежемесячные платежи
   */
  void OutputData(double over_payment, double total_payment,
                  std::vector<double> monthly_payments);

 public:
  /**
   * @brief Указатель на кнопку вычисления кредитных условий
   */
  QPushButton *eval_credit_;

 private:
  /**
   * @brief Функция инициализации полей ввода
   *
   * @return Указатель на виджет с полями ввода
   */
  QGroupBox *AddInputGroupBox();
  /**
   * @brief Функция инициализации полей вывода
   *
   * @return Указатель на виджет с полями вывода
   */
  QGroupBox *AddOutputGroupBox();

 private:
  /* Input block */
  /**
   * @brief Указатель на поле ввода размера кредита
   */
  QDoubleSpinBox *credit_amount_;
  /**
   * @brief Указатель на поле ввода срока кредита
   */
  QDoubleSpinBox *credit_term_;
  /**
   * @brief Указатель на поле ввода процентной ставки по кредиту
   */
  QDoubleSpinBox *credit_interest_;
  /**
   * @brief Указатель на поле ввода типа кредита
   */
  QComboBox *credit_type_;
  /* Output block */
  /**
   * @brief Указатель на лист полей вывода платежей по кредиту
   */
  QListWidget *payment_monthly_;
  /**
   * @brief Указатель на поле вывода переплаты по кредиту
   */
  QLineEdit *payment_over_;
  /**
   * @brief Указатель на поле вывода общей суммы платежа по кредиту
   */
  QLineEdit *payment_total_;
};

}  // namespace s21
#endif  // VIEW_CREDITWINDOW_H_

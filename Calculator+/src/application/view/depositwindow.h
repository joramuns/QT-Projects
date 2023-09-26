/**
 * @file
 * @brief Заголовочный файл с описанием класса DepositWindow
 *
 * Данный класс является дополнительным классом view приложения калькулятор.
 * В нем содержатся поля ввода данных для расчета депозита, а также кнопка
 * расчета кредита и поля вывода данных по депозиту.
 */
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
/**
 * @brief Класс отображения дополнительного функционала приложения - депозитный
 * калькулятор.
 */
class DepositWindow : public QWidget {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса по умолчанию, инициализирует приватные поля
   */
  DepositWindow();

  /* Accessors */
  /**
   * @brief Функция, возвращающая значение поля ввода суммы депозита
   *
   * @return Сумма депозита
   */
  double GetDepositAmount() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода срока депозита
   *
   * @return Срок депозита
   */
  int GetDepositTerm() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода процентной ставки депозита
   *
   * @return Процентная ставка
   */
  double GetDepositRate() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода налоговой ставки с прибыли
   *
   * @return Налоговая ставка
   */
  double GetDepositTaxRate() const noexcept;
  /**
   * @brief Функция, возвращающая тип периодических выплат в соответствии с enum
   *
   * @return Значение периода enum
   */
  int GetPeriodicity() const noexcept;
  /**
   * @brief Функция, возвращающая тип депозита
   *
   * @return 1 - с капитализацией, 0 без капитализации
   */
  bool GetCapitalization() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода дня пополнения депозита
   *
   * @return День пополнения депозита
   */
  double GetReplenishmentDay() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода суммы пополнения депозита
   *
   * @return Сумма пополнения депозита
   */
  double GetReplenishmentAmount() const noexcept;
  /**
   * @brief Функция, возвращающая номер выделенного поля в списке пополнений
   * депозита (нумерация с 0)
   *
   * @return Номер выделенного поля пополнения депозита
   */
  int GetCurrentReplenishment() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода дня снятия с депозита
   *
   * @return День снятия с депозита
   */
  double GetWithdrawalDay() const noexcept;
  /**
   * @brief Функция, возвращающая значение поля ввода суммы снятия с депозита
   *
   * @return Сумма снятия с депозита
   */
  double GetWithdrawalAmount() const noexcept;
  /**
   * @brief Функция, возвращающая номер выделенного поля в списке снятий с
   * депозита (нумерация с 0)
   *
   * @return Номер выделенного поля снятия с депозита
   */
  int GetCurrentWithdrawal() const noexcept;

  /* Mutators */
  /**
   * @brief Функция добавления пополнения депозита в список пополнений депозита
   *
   * @param item Пара значений - день, сумма
   */
  void AddReplenishment(const std::pair<double, double> &item);
  /**
   * @brief Функция очищения списка пополнений депозита
   */
  void ClearReplenishment();
  /**
   * @brief Функция добавления пополнения депозита в список снятий с депозита
   *
   * @param item Пара значений - день, сумма
   */
  void AddWithdrawal(const std::pair<double, double> &item);
  /**
   * @brief Функция очищения списка снятий с депозита
   */
  void ClearWithdrawal();
  /**
   * @brief Функция прокрутки вниз отображения списков пополнений и снятий
   */
  void ScrollLists() noexcept;
  /**
   * @brief Функция добавления выплаты в список выплат в поле вывода
   *
   * @param payoff
   */
  void AddPayoff(const double payoff);
  /**
   * @brief Функция очистки поля списка выплат в поле вывода
   */
  void ClearPayoff() noexcept;
  /**
   * @brief Функция установки прибыли депозита в поле вывода
   *
   * @param profit Сумма прибыли
   */
  void SetTotalProfit(const double profit) noexcept;
  /**
   * @brief Функция установки суммы налога на прибыль в поле вывода
   *
   * @param tax Сумма налога
   */
  void SetTaxAmount(const double tax) noexcept;
  /**
   * @brief Функция установки суммы на счету к окончанию срока договора депозита
   * в поле вывода
   *
   * @param amount
   */
  void SetEndAmount(const double amount) noexcept;

 public:
  /**
   * @brief Указатель на кнопку добавления пополнения депозита
   */
  QPushButton *add_replenishment_;
  /**
   * @brief Указатель на кнопку удаления пополнения депозита
   */
  QPushButton *remove_replenishment_;

  /**
   * @brief Указатель на кнопку добавления снятия с депозита
   */
  QPushButton *add_withdrawal_;
  /**
   * @brief Указатель на кнопку удаления снятия с депозита
   */
  QPushButton *remove_withdrawal_;

  /**
   * @brief Указатель на кнопку вычисления депозитных условий
   */
  QPushButton *eval_deposit_;

 private:
  /**
   * @brief Функция инициализации полей ввода
   *
   * @return Указатель на виджет с полями ввода
   */
  QGroupBox *AddInputGroupBox();
  /**
   * @brief Функция инициализации дополнительных полей ввода - списки пополнения
   * и снятий
   *
   * @return Указатель на виджет с полями ввода
   */
  QGroupBox *AddExtraGroupBox();
  /**
   * @brief Функция инициализации полей вывода
   *
   * @return Указатель на виджет с полями вывода
   */
  QGroupBox *AddOutputGroupBox();

 private:
  enum Periodicity { kDay = 1, kMonth = 30, kQuarter = 90, kYear = 365 };
  /* Input block */
  /**
   * @brief Указатель на поле ввода размера депозита
   */
  QDoubleSpinBox *deposit_amount_;
  /**
   * @brief Указатель на поле ввода срока депозита
   */
  QDoubleSpinBox *deposit_term_;
  /**
   * @brief Указатель на поле ввода процентной ставки депозита
   */
  QDoubleSpinBox *deposit_interest_;
  /**
   * @brief Указатель на поле ввода налоговой ставки с прибыли депозита
   */
  QDoubleSpinBox *deposit_tax_rate_;
  /**
   * @brief Указатель на поле ввода периодичности выплат по депозиту
   */
  QComboBox *deposit_periodicity_;
  /**
   * @brief Указатель на поле ввода опции капитализации депозита
   */
  QCheckBox *capitalization_;

  /**
   * @brief Указатель на лист полей пополнений депозита
   */
  QListWidget *replenishments_list_;
  /**
   * @brief Указатель на поле ввода дня пополнения депозита
   */
  QDoubleSpinBox *replenishment_day_;
  /**
   * @brief Указатель на поле ввода суммы пополнения депозита
   */
  QDoubleSpinBox *replenishment_amount_;

  /**
   * @brief Указатель на лист полей ввода снятий с депозита
   */
  QListWidget *withdrawals_list_;
  /**
   * @brief Указатель на поле ввода дня снятий с депозита
   */
  QDoubleSpinBox *withdrawal_day_;
  /**
   * @brief Указатель на поле ввода суммы снятий с депозита
   */
  QDoubleSpinBox *withdrawal_amount_;

  /* Output block */
  /**
   * @brief Указатель на лист полей вывода выплат
   */
  QListWidget *payoffs_list_;
  /**
   * @brief Указатель на поле вывода прибыли с депозита
   */
  QLineEdit *total_profit_;
  /**
   * @brief Указатель на поле вывода сумма налогы с прибыли депозита
   */
  QLineEdit *tax_amount_;
  /**
   * @brief Указатель на поле вывода суммы на счету после окончания срока
   * договора депозита
   */
  QLineEdit *deposit_end_amount_;
};

}  // namespace s21
#endif  // VIEW_DEPOSITWINDOW_H_

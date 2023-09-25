/**
 * @file
 * @brief Заголовочный файл с описанием класса DepositCalc
 *
 * Данный класс является моделью для депозитного калькулятора в соответствии с
 * паттерном MVC в приложении калькулятора.
 */
#ifndef MODEL_DEPOSIT_H_
#define MODEL_DEPOSIT_H_

#include <cmath>
#include <map>
#include <vector>

namespace s21 {
/**
 * @brief Класс депозитного калькулятора, хранит в себе входные данные, делает
 * расчет в зависимости от типа депозита и хранит исходные данные
 */
class DepositCalc final {
 public:
  /**
   * @brief Конструктор класса, инициализирует приватные поля
   */
  DepositCalc() noexcept;

  /* Accessors */
  /**
   * @brief Функция для получения текущего списка пополнений депозита
   *
   * @return Возвращает константную мапу, содержащую в себе пару значений "день"
   * и "сумма" пополнений
   */
  const std::map<double, double> &GetReplenishmentList() const noexcept;
  /**
   * @brief Функция для получения текущего списка снятий с депозита
   *
   * @return Возвращает константную мапу, содержащую в себе пару значений "день"
   * и "сумма" снятий
   */
  const std::map<double, double> &GetWithdrawalList() const noexcept;
  /**
   * @brief Функция для получения списка выплат по депозиту
   *
   * @return Возвращает константный вектор, содержащий в себе выплаты по
   * депозиту
   */
  const std::vector<double> &GetPayoffsList() const noexcept;
  /**
   * @brief Функция для получения суммы заработанных средств с депозита
   *
   * @return Возвращает сумму выплат
   */
  double GetTotalProfit() const noexcept;
  /**
   * @brief Функция для получения суммы налога с прибыли по депозиту
   *
   * @return Возвращает сумму налога
   */
  double GetTaxCharge() const noexcept;
  /**
   * @brief Функция для получения количества денежных средств на счету по
   * истечению срока депозита
   *
   * @return Возвращает сумму остатка на депозите
   */
  double GetEndAmount() const noexcept;

  /* Mutators */
  /**
   * @brief Функция добавления операции пополнения депозита
   *
   * @param day День пополнения
   * @param amount Сумма пополнения
   */
  void AddReplenishment(double day, double amount) noexcept;
  /**
   * @brief Функция удаления операции пополнения депозита
   *
   * @param number Порядковый номер в списке пополнений. Нумерация с 0
   */
  void RemoveReplenishment(int number) noexcept;
  /**
   * @brief Функция добавления операции снятия с депозита
   *
   * @param day День снятия
   * @param amount Сумма снятия
   */
  void AddWithdrawal(double day, double amount) noexcept;
  /**
   * @brief Функция удаления операции снятия с депозита
   *
   * @param number Порядковый номер в списке снятий. Нумерация с 0
   */
  void RemoveWithdrawal(int number) noexcept;
  /**
   * @brief Функция установки входных данных по условиям депозита
   *
   * @param amount Сумма депозита
   * @param term Срок депозита
   * @param rate Процентная ставка депозита
   */
  void SetDepositData(double amount, int term, double rate) noexcept;
  /**
   * @brief Функция установки типа депозита
   *
   * @param tax Налоговая ставка на прибыль
   * @param periodicity Периодичность выплат (число дней)
   * @param capitalization Депозит с капитализацией
   */
  void SetDepositType(double tax, int periodicity,
                      bool capitalization) noexcept;
  /**
   * @brief Функция вычисления депозита в соответствии с заданными условиями
   */
  void EvaluateDeposit() noexcept;

 private:
  /**
   * @brief Функция банковского округления для денежных средств
   *
   * @param number Ссылка на число, которое необходимо округлить по банковским
   * правилам
   */
  void BankRounding(double &number) const noexcept;
  /**
   * @brief Функция для получения натурального числа на определенном месте в
   * вещественном числе после запятой
   *
   * @param number Число для исследования
   * @param place Место искомого числа после запятой (нумерация с 1)
   *
   * @return Значение натурального числа
   */
  int GetFloatingDigit(const double number, int place) const noexcept;
  /**
   * @brief Функция для проверки движений по счету в определенный день
   *
   * @param day День для проверки
   *
   * @return Истина - есть движение, ложь - нет движений
   */
  [[nodiscard]] bool AccountMovement(const int day) noexcept;
  /**
   * @brief Функция перерасчета ежедневного начисления на депозит
   *
   * @return
   */
  [[nodiscard]] double RecalculateDaily() const noexcept;

 private:
  /* Input data */
  /**
   * @brief Сумма депозита
   */
  double amount_;
  /**
   * @brief Срок депозита
   */
  int term_;
  /**
   * @brief Процентная ставка депозита
   */
  double interest_rate_;
  /**
   * @brief Периодичность платежей (в днях)
   */
  int deposit_type_;
  /**
   * @brief Налоговая ставка
   */
  double tax_rate_;
  /**
   * @brief Капитализация
   */
  bool capitalization_;
  /**
   * @brief Список пополнений депозита
   */
  std::map<double, double> replenishments_;
  /**
   * @brief Список снятий с депозита
   */
  std::map<double, double> withdrawals_;
  /* Output data */
  /**
   * @brief Список выплат
   */
  std::vector<double> payoffs_;
  /**
   * @brief Прибыль по депозиту
   */
  double total_profit_;
  /**
   * @brief Итоговая сумма на депозите по истечению срока договора
   */
  double end_amount_;
  /**
   * @brief Сумма начисленного налога на прибыль
   */
  double tax_amount_;
};

}  // namespace s21
#endif  // MODEL_DEPOSIT_H_

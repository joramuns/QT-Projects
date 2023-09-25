/**
 * @file
 * @brief Заголовочный файл с описанием класса CreditCalc
 *
 * Данный класс является моделью для кредитного калькулятора в соответствии с
 * паттерном MVC в приложении калькулятора.
 */
#ifndef MODEL_CREDIT_H_
#define MODEL_CREDIT_H_

#include <cmath>
#include <vector>

namespace s21 {
/**
 * @brief Класс кредитного калькулятора, хранит в себе входные данные, делает
 * расчет в зависимости от типа кредита и хранит исходные данные
 */
class CreditCalc final {
 public:
  /**
   * @brief Конструктор класса, инициализирует приватные поля
   */
  CreditCalc() noexcept;

  /* Accessors */
  /**
   * @brief Функция для получения списка платежей по кредиту
   *
   * @return Возвращает константный вектор, содержащий в себе платежи по кредиту
   */
  const std::vector<double> &GetPayments() const noexcept;
  /**
   * @brief Функция для получения суммы переплаты по кредиту
   *
   * @return Возвращает количество уплаченных процентов по кредиту
   */
  double GetOverpayment() const noexcept;
  /**
   * @brief Функция для получения суммы полного платежа по кредиту
   *
   * @return Возвращает сумму выплаты по кредиту
   */
  double GetTotalPayment() const noexcept;

  /* Mutators */
  /**
   * @brief Функция определяет тип кредита и вызывает соответствующую приватную
   * функцию расчета кредита
   */
  void Calculate() noexcept;
  /**
   * @brief Функция, принимающая входные данные по кредиту из контроллера в
   * соответствии с паттерном MVC
   *
   * @param amount Сумма кредита
   * @param term Срок кредита
   * @param interest_rate Процентная ставка кредита
   * @param credit_type Тип кредита: 1 - дифференцированный, 0 - аннуитетный
   */
  void SetData(double amount, double term, double interest_rate,
               int credit_type) noexcept;

 private:
  /**
   * @brief Функция расчета аннуитетного кредита
   */
  void CalculateAnnuity() noexcept;
  /**
   * @brief Функция расчета дифференцированного кредита
   */
  void CalculateDifferentiated() noexcept;
  /**
   * @brief Функция расчета платежа по аннуитетному кредиту
   */
  void AnnuityPayment() noexcept;
  /**
   * @brief Функция расчета платежа по дифференцированному кредиту
   */
  void DifferentiatedPayment() noexcept;

 private:
  /* Input data */
  /**
   * @brief Сумма кредита
   */
  double amount_;
  /**
   * @brief Срок кредита
   */
  double term_;
  /**
   * @brief Процентная ставка кредита
   */
  double interest_rate_;
  /**
   * @brief Тип кредита: 1 - дифференцированный, 0 - аннуитетный
   */
  int credit_type_;

  /* Output data */
  /**
   * @brief Список платежей по кредиту
   */
  std::vector<double> payments_;
  /**
   * @brief Переплата по кредиту
   */
  double overpayment_;
  /**
   * @brief Общая сумма платежа по кредиту
   */
  double total_payment_;
};

}  // namespace s21
#endif  // MODEL_CREDIT_H_

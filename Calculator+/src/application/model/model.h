/**
 * @file
 * @brief Заголовочный файл с описанием класса Model
 *
 * Данный класс является основным классом для калькулятора, наследуется от
 * классов InfixExpr и PostfixExpr, а также хранит в себе модели кредитного и
 * депозитного калькуляторов в виде экземпляров классов CreditCalc и DepositCalc
 */
#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <iomanip>
#include <stack>

#include "credit.h"
#include "deposit.h"
#include "infix.h"
#include "postfix.h"

namespace s21 {
/**
 * @brief Класс модели, наследуется от классов инфиксной нотации и постфиксной
 * нотации выражений, может конвертировать из одной в другую, а также делать
 * вычисления и возвращать значение выражения в числовом или строковом виде.
 */
class Model final : public InfixExpr, public PostfixExpr {
 public:
  /**
   * @brief Конструктор класс по умолчанию
   */
  Model() = default;

  /* Mutators */
  /**
   * @brief Функция конвертирует выражение из инфиксной нотации в постфиксную
   * нотацию
   */
  void Convert() noexcept;
  /**
   * @brief Функция очищает модель
   */
  void ClearModel() noexcept;

  /* Calculators */
  /**
   * @brief Функция вычисляет значение хранящегося выражения
   *
   * @return Значение результата
   */
  [[nodiscard]] double Evaluate() noexcept;
  /**
   * @brief Функция вычисляет значение хранящегося выражения и конвертирует
   * выражение со значением в строковый вид
   *
   * @return Строка выражения и значения результата
   */
  [[nodiscard]] const std::string GetResult() noexcept;
  /**
   * @brief Функция вычисляет значения выражения с переменной в заданных рамках
   *
   * @param value_borders Вектор из 4 значений - Х и У области значений и Х и У
   * области определения функции
   *
   * @return Пара векторов со значениями Х и У
   */
  [[nodiscard]] const std::pair<std::vector<double>, std::vector<double>>
  GetCoordinates(const std::vector<double> &value_borders);

  /* Debug output */
  /* void OutputModel() noexcept; */

 public:
  /**
   * @brief Экземпляр класса модели кредитного калькулятора
   */
  CreditCalc credit_model_;
  /**
   * @brief Экземпляр класса модели депозитного калькулятора
   */
  DepositCalc deposit_model_;

 private:
  /**
   * @brief Вычисление выражения из двух операндов и оператора
   *
   * @param a Операнд слева
   * @param b Операнд справа
   * @param math_operator Оператор между операндами
   *
   * @return Экземпляр класса Element со результатом операции
   */
  [[nodiscard]] const Element Calculate(const Element &a, const Element &b,
                                        OpType math_operator) const noexcept;
  /* Overload for unary operators */
  /**
   * @brief Вычисление выражения из операнда и оператора
   *
   * @param a Операнд
   * @param math_operator Оператор
   *
   * @return Экземпляр класса Element со результатом операции
   */
  [[nodiscard]] const Element Calculate(const Element &a,
                                        OpType math_operator) const noexcept;
};

}  // namespace s21
#endif  // MODEL_MODEL_H_

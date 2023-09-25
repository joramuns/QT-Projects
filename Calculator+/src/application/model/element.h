/**
 * @file
 * @brief Заголовочный файл с описанием класса Element
 *
 * Данный класс являет собой тип данных, используемый в расчетах математических
 * выражений. Может быть как оператором, так и операндом выражения.
 */
#ifndef MODEL_ELEMENT_H_
#define MODEL_ELEMENT_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace s21 {
/**
 * @brief Класс модели, являющейся специализированным типом данных для
 * математических выражений. Может быть как оператором, так и операндом
 * выражения. Поддерживает перегрузки математических действий между собой.
 */
class Element final {
 public:
  /**
   * @brief Конструктор класса, инициализирует переменные
   */
  Element() noexcept;
  /**
   * @brief Конструктор класса для оператора выражения, устанавливает флаг
   * оператора и присваивает значение тип оператора
   *
   * @param input Тип оператора в соответствии с enum класса
   */
  explicit Element(const int input) noexcept;
  /**
   * @brief Конструктор класса для операнда, являет собой вещественное число
   *
   * @param input Вещественной число операнд выражения
   */
  explicit Element(const double input) noexcept;
  /**
   * @brief Конструктор класса для операнда, создает операнд исходя из символа
   * числа
   *
   * @param input Символ числа
   */
  explicit Element(const char input) noexcept;

  /* Accessors */
  /**
   * @brief Функция проверяет, является ли экземпляр класса оператором
   *
   * @return Истина - является оператором, ложь - не является оператором
   */
  [[nodiscard]] bool IsOperator() const noexcept;
  /**
   * @brief Функция проверяет, является ли экземпляр класса переменной
   *
   * @return Истина - является переменной, ложь - не является переменной
   */
  [[nodiscard]] bool IsVariable() const noexcept;
  /**
   * @brief Функция возвращает значение экземпляра класса
   *
   * @return Число, хранящееся в экземпляре класса
   */
  [[nodiscard]] double GetValue() const noexcept;
  /**
   * @brief Функция возвращает приоритет оператора
   *
   * @return Приоритет в соответствии с enum класса, вычисляется с помощью
   * десятичного логарифма
   */
  [[nodiscard]] int GetPriority() const noexcept;

  /* Mutators */
  /**
   * @brief Функция посимвольного добавления чисел к операнду
   *
   * @param input Сивол для добавления
   */
  void AppendNumber(const char input) noexcept;
  /**
   * @brief Функция помечает оператор унарным
   */
  void SetUnary() noexcept;
  /**
   * @brief Функция подставляет значение в переменную
   *
   * @param number Значение переменной
   */
  void SetValue(const double number) noexcept;

  /* Overload operator methods */
  /**
   * @brief Перегрузка сложения двух экземпляров класса
   *
   * @param other Второй операнд
   *
   * @return Результат вычисления
   */
  Element operator+(const Element &other) const noexcept;
  /**
   * @brief Перегрузка вычитания двух экземпляров класса
   *
   * @param other Второй операнд
   *
   * @return Результат вычисления
   */
  Element operator-(const Element &other) const noexcept;
  /**
   * @brief Перегрузка остатка от деления двух экземпляров класса
   *
   * @param other Второй операнд
   *
   * @return Результат вычисления
   */
  Element operator%(const Element &other) const noexcept;
  /**
   * @brief Перегрузка умножения двух экземпляров класса
   *
   * @param other Второй операнд
   *
   * @return Результат вычисления
   */
  Element operator*(const Element &other) const noexcept;
  /**
   * @brief Перегрузка деления двух экземпляров класса
   *
   * @param other Второй операнд
   *
   * @return Результат вычисления
   */
  Element operator/(const Element &other) const noexcept;
  /**
   * @brief Перегрузка возведения в степень экземпляров класса
   *
   * @param other Степень возведения
   *
   * @return Результат вычисления
   */
  Element operator^(const Element &other) const noexcept;
  /**
   * @brief Перегрузка разименования экземпляра класса
   *
   * @return Значение экземпляра в строчном виде
   */
  std::string operator*() const noexcept;

  /* Unary operation methods */
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Синус
   */
  Element sin() const noexcept;
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Косинус
   */
  Element cos() const noexcept;
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Тангенс
   */
  Element tan() const noexcept;
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Арксинус
   */
  Element asin() const noexcept;
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Арккосинус
   */
  Element acos() const noexcept;
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Арктангенс
   */
  Element atan() const noexcept;
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Корень
   */
  Element sqrt() const noexcept;
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Натуральный логарифм
   */
  Element ln() const noexcept;
  /**
   * @brief Вычисление унарной операции для экземпляра класса
   *
   * @return Десятичный логарифм
   */
  Element log() const noexcept;

 public:
  /* Priority is shown by rang of 10 power */
  /**
   * @brief Типы возможных операторов, при смене приоритета тип домножается на
   * 10
   */
  enum OperatorType {
    kAddition = 1,
    kSubtraction,
    kUnaryAddition,
    kUnarySubtraction,
    kMultiplication = 10,
    kDivision,
    kModulus,
    kPower,
    kSin = 1000,
    kCos,
    kTan,
    kAsin,
    kAcos,
    kAtan,
    kSqrt,
    kLn,
    kLog,
    kBracketOpen = 10000,
    kBracketClose
  };

  /**
   * @brief Типы приоритетов операторов
   */
  enum PriorityType {
    kSubAdd = 0,
    kMulDivModPow,
    kTrigonometry = 3,
    kBrackets
  };

 private:
  /**
   * @brief Функция для проверки возможности вставки знака "е" (научная нотация
   * числа) в экземпляр класса
   *
   * @param last_char Последний символ в строчном представлении экземпляра
   * класса
   *
   * @return Истина - вставка возможна, ложь - вставка невозможна
   */
  bool CheckE(const char last_char) noexcept;
  /**
   * @brief Функция для проверки возможности вставки знака "." (разделитель
   * десятичной части вещественного числа) в экземпляр класса
   *
   * @return Истина - вставка возможна, ложь - вставка невозможна
   */
  bool CheckDot() noexcept;
  /**
   * @brief Проверка возможности вставки дополнительного числа в
   * экспоненциальной записи числа, ограниченно 2 числами
   *
   * @return Истина - вставка возможна, ложь - вставка невозможна
   */
  bool CheckDigit() noexcept;

 private:
  /**
   * @brief Является ли экземпляр класса оператором
   */
  bool is_operator_;
  /**
   * @brief Значение экземпляра класса
   */
  double value_;
  /**
   * @brief Значение экземпляра класса в строчном представлении
   */
  std::string string_value_{};
};

}  // namespace s21

/* Debug output for element */
/* std::ostream &operator<<(std::ostream &os, const s21::Element &output); */

#endif  // MODEL_ELEMENT_H_

/**
 * @file
 * @brief Заголовочный файл с описанием класса InfixExpr
 *
 * Данный класс формирует и хранит в себе математическое выражение в инфиксной
 * нотации.
 */
#ifndef MODEL_INFIX_H_
#define MODEL_INFIX_H_

#include <deque>
#include <memory>
#include <vector>

#include "element.h"

namespace s21 {
/**
 * @brief Класс модели, являющийся математическим выражением в стандартной
 * инфиксной нотации. Позволяет составлять выражение из класса Element.
 * Проверяет валидность введенного выражения. Все элементы в выражении
 * динамически аллоцированы, обусловленно тем, что есть возможность установки
 * значения в переменную. Кроме самого выражения хранится вектор умных
 * указателей на все переменные в выражении. Это сделано для того, чтобы при
 * установке значения переменных не проходить по всему выражению, а
 * устанавливать значения в конкретные элементы.
 */
class InfixExpr {
  using elem_iterator = std::deque<std::unique_ptr<Element>>::iterator;

 public:
  /**
   * @brief Конструктор по умолчанию
   */
  InfixExpr() = default;

 public:
  /* Accessors */
  /**
   * @brief Функция возвращает константную ссылку на хранящееся выражение в деке
   */
  [[nodiscard]] const std::deque<std::unique_ptr<Element>> &GetInfixData()
      const noexcept;
  /* Accessors */
  /**
   * @brief Функция возвращает хранящееся выражение в строчном виде
   */
  [[nodiscard]] const std::string GetInfixString() const noexcept;

  /* Mutators */
  /**
   * @brief Создает динамически аллоцированный с помощью уникального умного
   * указания класс Element типа оператор и отправляет в функцию добавления в
   * выражение
   *
   * @param type Тип оператора в соответствии с enum класса Element
   */
  void AddElement(const int type);
  /**
   * @brief Создает динамически аллоцированный с помощью уникального умного
   * указания класс Element типа операнд и отправляет в функцию добавления в
   * выражение
   *
   * @param number Число для добавление в класс Element в строчном виде
   */
  void AddElement(const char number);
  /**
   * @brief Функция добавление созданного динамически экземпляра класса элемент
   * в выражение
   *
   * @param token Уникальный умный указатель на созданный элемент
   */
  void AddElement(std::unique_ptr<Element> token) noexcept;
  /**
   * @brief Функция валидации введенного выражения, состоит из трех проверок -
   * размер выражения, конец выражения, начало выражения и проход по всем
   * элементам в выражении для выявления неверного сочетания элементов
   *
   * @return Код ошибки (TODO: зафиксировать коды ошибок)
   */
  int ValidateExpr() noexcept;
  /**
   * @brief Функция сброса хранящегося математического выражения
   */
  void ClearInfixExpr() noexcept;
  /**
   * @brief Функция, добавляющая символ в последний операнд выражения
   *
   * @param number Символ для добавления
   */
  void AppendNumber(const char number) noexcept;
  /**
   * @brief Функция подмены всех переменных в выражении определенным значением
   *
   * @param number Значение переменной
   */
  void SetVariables(const double number) noexcept;

  /* Excluded due to perfect visual fitment without this button */
  /* void DelElement() noexcept; */

 private:
  /**
   * @brief Функция возвращает хранящееся выражение в строчном виде
   */
  [[nodiscard]] bool LastIsOperator() const noexcept;
  /**
   * @brief Функция возвращает хранящееся выражение в строчном виде
   */
  [[nodiscard]] bool LastIsVariable() const noexcept;
  /**
   * @brief Проверка размера выражения, допустим размер 1, если в выражении
   * операнд, но недопустим единственный оператор в выражении
   *
   * @param iter_begin Умный указатель на начало выражения
   *
   * @return Код ошибки (TODO: зафиксировать коды ошибок)
   */
  [[nodiscard]] int SizeValid(const elem_iterator iter_begin) const noexcept;
  /**
   * @brief Проверка начала выражения, недопустимы бинарные операторы в начале
   * выражения
   *
   * @param iter_begin Умный указатель на начало выражения
   *
   * @return Код ошибки (TODO: зафиксировать коды ошибок)
   */
  [[nodiscard]] int BeginValid(const elem_iterator iter_begin) const noexcept;
  /**
   * @brief Проверка конца выражения, недопустимы операторы кроме закрывающей
   * скобки в конце
   *
   * @return Код ошибки (TODO: зафиксировать коды ошибок)
   */
  [[nodiscard]] int EndValid() const noexcept;
  /**
   * @brief Проверка попарно каждые два элемента от начала до конца выражения,
   * обработка ошибочного ввода
   *
   * @param iter_begin Умный указатель на начало выражения
   *
   * @return Код ошибки (TODO: зафиксировать коды ошибок)
   */
  [[nodiscard]] int MiddleValid(elem_iterator iter_begin) const noexcept;
  /**
   * @brief Проверка двух конкретных элементов на последовательную совместимость
   *
   * @param type_first Умный указатель на первый элемент в паре
   * @param type_second Умный указатель на второй элемент в паре
   *
   * @return Код ошибки (TODO: зафиксировать коды ошибок)
   */
  [[nodiscard]] int DoubleOperator(
      const elem_iterator type_first,
      const elem_iterator type_second) const noexcept;

 private:
  /**
   * @brief Список умных указателей на математическое выражение
   */
  std::deque<std::unique_ptr<Element>> infix_data_;
  /**
   * @brief Список умных указателей на переменные в выражении
   */
  std::vector<Element *> var_array_;
};

}  // namespace s21

#endif  // MODEL_INFIX_H_

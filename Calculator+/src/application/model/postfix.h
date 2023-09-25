/**
 * @file
 * @brief Заголовочный файл с описанием класса PostfixExpr
 *
 * Данный класс формирует и хранит в себе математическое выражение в постфиксной
 * нотации.
 */
#ifndef MODEL_POSTFIX_H_
#define MODEL_POSTFIX_H_

#include <deque>
#include <iostream>

#include "element.h"

namespace s21 {
/**
 * @brief Класс модели, являющийся математическим выражением в
 * постфиксной нотации. Составляет выражение на основе правил, описанных Яном
 * Лукасевичем. В данном классе используются два стека - стек очереди и выходной
 * стек с готовым выражением в обратной польской нотации.
 */
class PostfixExpr {
 public:
  /**
   * @brief Конктруктор класса по умолчанию
   */
  PostfixExpr() = default;

 protected:
  using OpType = s21::Element::OperatorType;
  /* Modifiers */
  /**
   * @brief Функция добавления операнда в выражение
   *
   * @param number Экземпляр класса Element с операндом
   */
  void AddOperand(const Element &number) noexcept;
  /**
   * @brief Функция добавления оператора в выражение
   *
   * @param number Экземпляр класса Element с оператором
   */
  void AddOperator(const Element &operation) noexcept;
  /**
   * @brief Функция сброса хранящегося математического выражения
   */
  void ClearPostfixExpr() noexcept;
  /**
   * @brief Функция переброса из стека очереди в выходной стек всего до конца
   * стека или до открывающей скобки
   */
  void PopAndPushAll() noexcept;

  /* Accessors */
  /**
   * @brief Возвращает константную ссылку на хранящееся выражение
   *
   * @return Стек постфиксного выражения из экземпляром класса Element
   */
  [[nodiscard]] const std::deque<Element> &GetPostfixExpr() const noexcept;

  /* Debug accessor */
  /* [[nodiscard]] const std::deque<Element> &GetQueue() const noexcept; */

 private:
  /**
   * @brief Функция достает экземпляр класса Element из стека очереди и кладет в
   * выходной стек
   */
  void PopAndPush() noexcept;
  /**
   * @brief Функция проверяет наличие открывающей скобки наверху выходной
   * очереди
   *
   * @return Истина - открывающая скобка, ложь - любой другой элемент
   */
  [[nodiscard]] bool TopOpenBracket() const noexcept;

 private:
  /* Fields */
  /**
   * @brief Выходной стек с готовым выражением в обратной польской нотации
   */
  std::deque<Element> stack_out_;
  /**
   * @brief Стек очереди с элементами
   */
  std::deque<Element> queue_stack_;
};

}  // namespace s21

#endif  // MODEL_POSTFIX_H_

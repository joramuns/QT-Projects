/**
 * @file
 * @brief Заголовочный файл с описанием класса controller
 *
 * Данный класс связывает между собой классы model и view в соответствии с
 * паттерном MVC в приложении калькулятора.
 */
#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <QObject>

#include "../model/model.h"
#include "../view/calcwindow.h"

namespace s21 {
/**
 * @brief Класс контроллера, наследуется от QObject для возможности подключения
 * сигналов от класса view. При этом, важно отметить, что сам по себе фреймворк
 * QT построен при помощи паттерна MV, где сигналы от графического интерфейса
 * обрабатываются в классе view. Так как по требованию проекта мы обязаны делать
 * в ином архитектурном решении, приходится откусывать кусок функционала от view
 * класса.
 */
class Controller : public QObject {
  Q_OBJECT

 public:
  Controller() = delete;
  /**
   * @brief Конструктор класса
   *
   * @param cview Ссылка на класс view
   * @param cmodel Ссылка на класс model
   *
   * Данный класс может создаться только с привязкой к классам model и view, все
   * остальные типы конструкторов удалены.
   */
  Controller(CalcWindow *cview, Model *cmodel);
  Controller(const Controller &other) = delete;
  Controller(Controller &&other) = delete;
  Controller &operator=(const Controller &other) = delete;
  Controller &operator=(Controller &&other) = delete;

 public slots:
  /**
   * @brief Функция, привязанная к сигналу кнопки удаления ввода
   */
  void ClearButton() noexcept;
  /**
   * @brief Функция, привязанная к сигналу кнопок с операндами
   */
  void NumButton() noexcept;
  /**
   * @brief Функция, привязанная к сигналу кнопок с операторами
   */
  void OperButton() noexcept;
  /**
   * @brief Функция, привязанная к сигналу кнопки расчета выражения
   */
  void EvalButton() noexcept;
  /**
   * @brief Функция, привязанная к сигналу кнопки отрисовки графика
   */
  void MakePlot();

  /* Credit calc */
  /**
   * @brief Функция, привязанная к сигналу кнопки вычисления кредита
   */
  void CreditEvalButton() noexcept;

  /* Deposit calc */
  /**
   * @brief Функция, привязанная к сигналу кнопки добавления пополнения депозита
   */
  void DepositAddReplenishment() noexcept;
  /**
   * @brief Функция, привязанная к сигналу кнопки удаления пополнения депозита
   */
  void DepositRemoveReplenishment() noexcept;
  /**
   * @brief Функция, привязанная к сигналу кнопки добавления снятия с депозита
   */
  void DepositAddWithdrawal() noexcept;
  /**
   * @brief Функция, привязанная к сигналу кнопки удаления снятия с депозита
   */
  void DepositRemoveWithdrawal() noexcept;
  /**
   * @brief Функция, привязанная к сигналу кнопки вычисления депозита
   */
  void DepositEvalButton() noexcept;

 private:
  /**
   * @brief Функция осуществляет подстановку значения переменной
   */
  void VariableSet() noexcept;
  /**
   * @brief Функция отрисовывает данные из модели - выражение и результат
   * вычислений
   */
  void Render() const noexcept;
  /**
   * @brief Функция забирает из view данные кредитного калькулятора и отправляет
   * в соответствующую модель
   */
  void SetCreditData() noexcept;
  /**
   * @brief Функция отрисовывает данные из модели кредитного калькулятора -
   * результат вычисления
   */
  void RenderCredit() noexcept;
  /**
   * @brief Функция отрисовывает изменения в списке пополнений депозита
   */
  void RenderReplenishment() const noexcept;
  /**
   * @brief Функция отрисовывает изменения в списке снятий с депозита
   */
  void RenderWithdrawal() const noexcept;
  /**
   * @brief Функция забирает из view данные депозитного калькулятора и
   * отправляет в соответствующую модель
   */
  void SetDepositData() noexcept;
  /**
   * @brief Функция отрисовывает данные из модели депозитного калькулятора -
   * результат вычисления
   */
  void RenderDeposit() const noexcept;
  /* MVC */
  /**
   * @brief Приватное поле, которое хранит в себе указатель на класс view
   */
  CalcWindow *view_;
  /**
   * @brief Приватное поле, которое хранит в себе указатель на класс model
   */
  Model *model_;
};

}  // namespace s21
#endif  // CONTROLLER_CONTROLLER_H_

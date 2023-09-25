/**
 * @file
 * @brief Заголовочный файл с описанием класса CalcWindow
 *
 * Данный класс является основным классом view приложения калькулятор. В нем
 * содержатся кнопки ввода, поля ввода и вывода, а также график функции.
 * Дополнительно, создаются экземпляры классов CreditWindow и DepositWindow и
 * отображаются при запуске приложения.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <memory>
#define QCUSTOMPLOT_USE_LIBRARY
#include "../libs/qcustomplot/qcustomplot.h"
#include "../model/model.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "operatorbutton.h"

namespace s21 {
/**
 * @brief Класс отображения приложения, наследуется от QMainWindow. Содержит в
 * себе указатели на классы CreditWindow и DepositWindow
 */
class CalcWindow final : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса по умолчанию, инициализирует приватные поля
   */
  CalcWindow();

  /* Accessors */
  /**
   * @brief Функция, возвращающая значения полей ввода
   *
   * @param number Номер поля ввода (0 - значение переменной, 1-4 координаты Х и
   * У областей значений и определения функции)
   *
   * @return Значение поля ввода в строковом выражении
   */
  const std::string GetDomains(const int number) const noexcept;

  /* Mutators */
  /**
   * @brief Функция, устанавливающая в поле вывода выражение
   *
   * @param expression Задаваемое значение в строковом виде
   */
  void SetExpression(const std::string &expression) noexcept;
  /**
   * @brief Функция, добавляющая выражение и результат вычислений в поле вывода
   *
   * @param result Задаваемое выражение в строковом виде
   */
  void AddResults(const std::string &result) noexcept;
  /**
   * @brief Функция отрисовки графика функции
   *
   * @param x Вектор значений Х
   * @param y Вектор значений У
   * @param borders Вектор значений координат областей значений и определения
   * функции
   */
  void DrawPlot(const QVector<double> &x, const QVector<double> &y,
                const std::vector<double> &borders);

 public:
  /**
   * @brief Массив указателей на кнопки операндов калькулятора
   */
  std::array<QPushButton *, 13> num_buttons_;
  /**
   * @brief Массив указателей на кнопки операторов калькулятора
   */
  std::array<OperatorButton *, 17> operator_buttons_;
  /**
   * @brief Указатель на кнопку очистки поля ввода
   */
  QPushButton *clear_;
  /**
   * @brief Указатель на кнопку вычисления выражения
   */
  QPushButton *eval_;
  /**
   * @brief Указатель на кнопку отрисовки графика
   */
  QPushButton *make_plot_;

  /* Bonus part */
  /**
   * @brief Указатель на виджет кредитного калькулятора
   */
  CreditWindow *credit_window_;
  /**
   * @brief Указатель на виджет депозитного калькулятора
   */
  DepositWindow *deposit_window_;

 private:
  /**
   * @brief Функция инициализации кнопок операндов
   */
  void InitNumButtons();
  /**
   * @brief Функция инициализации кнопок операторов
   */
  void InitOperButtons();
  /**
   * @brief Функция инициализации полей ввода
   */
  void InitInputLines();
  /**
   * @brief Функция инициализации кнопок вычисления
   */
  void InitEvalButtons();
  /**
   * @brief Функция инициализации полей вывода
   */
  void InitOutput();

 private:
  /**
   * @brief Типы возможных операторов, при смене приоритета тип домножается на
   * 10
   */
  enum OperatorType {
    kAddition = 1,
    kSubtraction,
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
   * @brief Массив указателей на описание полей ввода
   */
  std::array<QLabel *, 5> input_labels_;
  /**
   * @brief Массив указателей на поля ввода
   */
  std::array<QLineEdit *, 5> input_lines_;
  /**
   * @brief Умный уникальный указатель на валидатор поля по регулярному
   * выражению
   */
  std::unique_ptr<QRegularExpressionValidator> regex_validator_;
  /**
   * @brief Указатель на виджет графика
   */
  QCustomPlot *plot_;
  /**
   * @brief Указатель на поле ввода выражения
   */
  QLabel *display_;
  /**
   * @brief Указатель на лист полей вывода вычисленного выражения
   */
  QListWidget *results_display_;
};

}  // namespace s21
#endif  // MAINWINDOW_H

#ifndef VIEW_H_
#define VIEW_H_

#include <QCloseEvent>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

// temp glwidget
#include "../model/context/glwidget.h"
#include "mainwidgets/app_management.h"
#include "settingswidgets/settingstab.h"
#include "transformwidgets/transform_tab.h"

namespace s21 {
/// @brief Класс верхнего уровня пользовательсокого интерфейса, который
/// организовывает инициализацию, коннекты и расположение управляющих элементов
/// интерфейса для пользователя
class View final : public QWidget {
  Q_OBJECT

 public:
  View() = delete;
  ~View();
  /// @brief Конструктор инициализирует поля, подключает кнопки к обработчикам и
  /// создает пользовательский интерфейс
  /// @param context  Указатель на виджет OpenGl
  explicit View(GLWidget *context);

  /// @brief Создает новый виджет по имени файла и добавляет его в лист виджетов
  /// @param filename Имя файла (абсолютный путь)
  void AddListWidgetItem(const std::string &model_info);

  /// @brief Удаляет из листа виджетов виджет 3-х мерного объекта по его номеру
  /// @param model_number Номер трехмерного объекта
  void RemoveListWidgetItem(int model_number);

 private slots:
  /// @brief Слот выпускающий сигнал обработчику на изменение координат 3-х
  /// мерного объекта
  /// @param value Значение величины изменений
  /// @param axis Ось изменений
  /// @param type Тип изменений
  /// @param model_number  ID модели
  void ViewTransformSlot(double value, char axis, int type, int model_number);

  /// @brief Слот выпускающий сигнал обработчику открытия файла 3-х мерного
  /// объекта
  /// @param filename Абсолютный путь к файлу 3-х мерного объекта
  void OpenFileSlot(QString filename);

  /// @brief Слот выпускающий сигнал закрытия файла 3-х мерного объекта
  void CloseFileSlot();

  /// @brief Слот выпускающий сигнал смены типа проекции 3-х мерного объекта
  /// @param index Тип проекции
  void SceneOptionSlot(int index);

  /// @brief Слот выпускающий сигнал смены типа отображения граней 3-х мерного
  /// объекта
  /// @param index Тип отображения граней
  void ExtraSceneOptionSlot(int index);

  /// @brief Слот выпускающий сигнал смены цвета заднего фона виджета  OpenGl
  /// @param scene_color Цвет заднего фона
  void SceneColorSlot(QColor scene_color);

  /// @brief Слот выпускающий сигнал смены цвета отображаемых вершин 3-х мерного
  /// объекта
  /// @param vertex_color Цвет вершин
  void VertexColorSlot(QVector3D vertex_color);

  /// @brief Слот выпускающий сигнал смены цвета отображаемых ребер 3-х мерного
  /// объекта
  /// @param edge_color Цвет ребер
  void EdgeColorSlot(QVector3D edge_color);

  /// @brief Слот выпускающий сигнал смены типа отображаемых вершин 3-х мерного
  /// объекта
  /// @param index Тип отображения вершин
  void VertexOptionSlot(int index);

  /// @brief Слот выпускающий сигнал смены типа отображаемых ребер 3-х мерного
  /// объекта
  /// @param index Тип отображения ребер
  void EdgeOptionSlot(int index);

  /// @brief Слот выпускающий сигнал смены размера отображаемых вершин 3-х
  /// мерного объекта
  /// @param value Величина значения отображаемых вершин
  void VertexSizeSlot(double value);

  /// @brief Слот выпускающий сигнал смены размера отображаемых ребер 3-х
  /// мерного объекта
  /// @param value Величина значения отображаемых ребер
  void EdgeSizeSlot(double value);
  void ScreenshotSlot(const QString &filename);
  void GifSlot(const QString &filename);

 signals:
  /// @brief Сигнал изменения координат 3-х мерного объекта
  /// @param value Значение величины изменений
  /// @param axis Ось изменений
  /// @param type Тип изменений
  /// @param model_number  ID модели
  void ViewTransformSignal(double value, char axis, int type, int model_number);

  /// @brief Сигнал открытия файла 3-х мерного объекта
  /// @param filename Абсолютный путь к файлу 3-х мерного объекта
  void OpenFileSignal(QString filename);

  /// @brief Сигнал закрытия файла 3-х мерного объекта
  /// @param model_number  ID 3-х мерного объекта
  void CloseFileSignal(int model_number);

  /// @brief Сигнал смены типа проекции 3-х мерного объекта
  /// @param index Тип проекции
  void SceneOptionSignal(int index);

  /// @brief Сигнал смены типа отображения граней 3-х мерного объекта
  /// @param index Тип отображения граней
  void ExtraSceneOptionSignal(int index);

  /// @brief Сигнал смены цвета заднего фона виджета  OpenGl
  /// @param scene_color Цвет заднего фона
  void SceneColorSignal(QColor scene_color);

  /// @brief Сигнал смены цвета отображаемых вершин 3-х мерного объекта
  /// @param vertex_color Цвет вершин
  void VertexColorSignal(QVector3D vertex_color);

  /// @brief Сигнал смены цвета отображаемых ребер 3-х мерного объекта
  /// @param edge_color Цвет ребер
  void EdgeColorSignal(QVector3D edge_color);

  /// @brief Сигнал смены типа отображаемых вершин 3-х мерного объекта
  /// @param index Тип отображения вершин
  void VertexOptionSignal(int index);

  /// @brief Сигнал смены типа отображаемых ребер 3-х мерного объекта
  /// @param index Тип отображения ребер
  void EdgeOptionSignal(int index);

  /// @brief Сигнал смены размера отображаемых вершин 3-х мерного объекта
  /// @param value Величина значения отображаемых вершин
  void VertexSizeSignal(double value);

  /// @brief Сигнал смены размера отображаемых ребер 3-х мерного объекта
  /// @param value Величина значения отображаемых ребер
  void EdgeSizeSignal(double value);
  void ScreenshotSignal(const QString &filename);
  void GifSignal(const QString &filename);

 private:
  void closeEvent(QCloseEvent *event);

 private:
  QGridLayout *main_layout_;
  GLWidget *gl_widget_;
  QListWidget *list_widget_;
};
}  // namespace s21

#endif  // VIEW_H_

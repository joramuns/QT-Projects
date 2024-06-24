/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса Controller
*/
#ifndef CPP4_3DVIEWER_V2_0_2_APPLICATION_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_2_APPLICATION_CONTROLLER_CONTROLLER_H_

#include <QWidget>

#include "../model/facade/facade.h"
#include "../view/view.h"

namespace s21 {
/// @brief Класс контроллер для обеспечения модульности связей отображения и
/// модели
class Controller final : public QObject {
  Q_OBJECT

 public:
  /// @brief Конструктор устанавливает связь между отображением и моделью
  /// @param v указатель на экземпляр класса отображения
  /// @param f укзаатель на экземпляр класса модели(фасада)
  Controller(View *v, Facade *f);

 private slots:
  /// @brief Слот обрабатывающий сигнал о трансформации модели
  /// @param value
  /// @param axis
  /// @param type
  /// @param model_number
  void ControllerTransformSlot(double value, char axis, int type,
                               int model_number);

  /// @brief Слот обрабатывающий открытие файла
  /// @param filename абсолютный путь к файлу
  void ControllerOpenFileSlot(QString filename);

  /// @brief Слот обрабатывающий закрытие файла
  /// @param model_number индекс 3-х мерного объекта
  void ControllerCloseFileSlot(int model_number);

  /// @brief Слот обрабатывающий смену проекции
  /// @param index тип проекции
  void ControllerSceneOptionSlot(int index);

  /// @brief Слот обрабатывающий смену типа отображения
  /// @param index тип отображения
  void ControllerExtraSceneOptionSlot(int index);

  /// @brief Слот обрабатывающий смену цвета сцены
  /// @param scene_color значение цвета сцены
  void ControllerSceneColor(QColor scene_color);

  /// @brief Слот обрабатывающий смену цвета вершин
  /// @param vertex_color цвет вершины
  void ControllerVertexColor(QVector3D vertex_color);

  /// @brief Слот обрабатывающий смену цвета ребер
  /// @param edge_color цвет ребер
  void ControllerEdgeColor(QVector3D edge_color);

  /// @brief Слот обрабатывающий смену типа отображения вершин
  /// @param index тип отображения вершин
  void ControllerVertexOption(int index);

  /// @brief Слот обрабатывающий смену типа отображения ребер
  /// @param index тип отображения ребер
  void ControllerEdgeOption(int index);

  /// @brief Слот обрабатывающий смену отображения величины вершин
  /// @param value значение велечины вершины
  void ControllerVertexSize(double value);

  /// @brief Слот обрабатывающий смену отображения величины ребер
  /// @param value значение величины ребер
  void ControllerEdgeSize(double value);

  void ControllerScreenshotSlot(const QString &filename);

  void ControllerGifSlot(const QString &filename);

 private:
  /// @brief Метод связывающий сигналы отображения со слотами обработчиками в
  /// контроллере
  void ConnectFields() const;

 private:
  View *view_;  ///< указатель на экземпляр класса отображения
  Facade *facade_;  ///< укзатель на экземпляр класса фасада
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_APPLICATION_CONTROLLER_CONTROLLER_H_

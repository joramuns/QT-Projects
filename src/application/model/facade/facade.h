/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса фасада, дающего пользователю
интерфейс взаимодействия с моделью, скрывая внутреннюю реализацию.
*/
#ifndef CPP4_3DVIEWER_V2_MODEL_FACADE_FACADE_H
#define CPP4_3DVIEWER_V2_MODEL_FACADE_FACADE_H

#include <vector>

#include "../context/glwidget.h"
#include "../object_model.h"
#include "../parser/parser.h"

namespace s21 {
/// @brief Класс реализует паттерн Фасад, дающий пользователю интерфейс
/// взаимодействия с моделью 3D_Viewer
class Facade {
 public:
  /// @brief Конструктор по умолчанию
  Facade();

  /// @brief Деструктор класса
  ~Facade();

  /// @brief Метод добавляет в модель обработку нового файла 3-х мерного объекта
  /// @param filename Абсолютный путь к файлу 3-х мерной модели в формате obj
  void AddModel(const std::string &filename) noexcept;

  /// @brief Метод удаляет из модели данные о 3-х мерном объекте
  /// @param model_number Индекс 3-х мерного объекта, которую необходимо удалить
  void RemoveModel(int model_number) noexcept;

  /// @brief Возвращает экземпляр класса 3-х мерного объекта по индексу
  /// @param index Индекс 3-х мерного объекта
  /// @return Экземпляр класса 3-х мерного объекта
  /* ObjectModel GetModel(const unsigned int index) const noexcept; */

  /// @brief Возвращает размер массива 3-х мерных объектов
  inline int GetCountModel() const noexcept { return models_; };

  /// @brief Возвращает указтель на виджет OpenGL
  inline GLWidget *GetContext() const noexcept { return context_; }

  // debug
  void PrintDate() const noexcept;

  /// @brief Метод позволяющий проводить вращение 3-х мерного объекта
  /// @param value Значение на которое необходимо произвести вращение
  /// @param axis Ось вокруг которой просиходит вращение
  /// @param model_number Индекс вращаемого 3-х мерного объекта
  void Rotate(double value, char axis, int model_number);

  /// @brief Метод позволяющий двигать 3-х мерный объект
  /// @param value Значение на которое необходимо двинуть
  /// @param axis  Ось вдоль которой происходит движение
  /// @param model_number Инедекс перемещаемого 3-х мерного объекта
  void Move(double value, char axis, int model_number);

  /// @brief Метод позволяющий масштабировать 3-х мерный объект
  /// @param value Значение масштабирования
  /// @param model_number Индекс масштабируемого 3-х мерного объекта
  void Scale(double value, int model_number);

  /* Scene management */

  /// @brief Метод позволяющий сменить тип проекции
  /// @param index Тип проекции
  void SwitchProjection(int index);

  /// @brief Метод позволяющий изменить тип отображения 3-х мерной модели
  /// @param index Тип отображения
  void SwitchWireframe(int index);

  /// @brief Метод позволяющий изменить цвет сцены
  /// @param scene_color Новый цвет сцены
  void ChangeSceneColor(QColor scene_color);

  /// @brief Метод позволяющий изменить цвет вершин 3-х мерного объекта
  /// @param vertex_color Новый цвет вершин
  void ChangeVertexColor(QVector3D vertex_color);

  /// @brief Метод позволяющий изменить цвет граней 3-х мерного объекта
  /// @param edge_color  Новый цвет граней
  void ChangeEdgeColor(QVector3D edge_color);

  /// @brief Метод позволящий изменить тип отображения вершин 3-х мерного
  /// объекта
  /// @param index Тип отображения вершин
  void ChangeVertexOption(int index);

  /// @brief Метод позволяющий изменить тип отображения граней 3-х мерного
  /// объекта
  /// @param index Тип отображения граней
  void ChangeEdgeOption(int index);

  /// @brief Метод позволяющий изменить размер вершин 3-х мерного объекта
  /// @param value Новое значение размера вершин
  void ChangeVertexSize(double value);

  /// @brief Метод позволяющий изменить размер ребер 3-х мерного объекта
  /// @param value Новое значение размера ребер
  void ChangeEdgeSize(double value);

 private:
  int models_ = 0;
  /* std::vector<ObjectModel> models_; ///< Вектор 3-х мерных объектов */
  GLWidget *context_;  ///<
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_FACADE_FACADE_H

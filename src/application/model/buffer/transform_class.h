/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса Axes
*/
#ifndef CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_TRANSFORM_CLASS_H_
#define CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_TRANSFORM_CLASS_H_

#include <QOpenGLShaderProgram>

namespace s21 {
/// @brief Класс Axes отвечает за тип и значение трансформаций 3-х мерного
/// объекта
class Axes {
 public:
  /// @brief Конструктор по умолчанию - удален
  Axes() = delete;

  /// @brief Конструктор определяющий значение трансформации
  /// @param init Значение трансформации
  explicit Axes(double init);

  /// @brief Фомрирует вектор трансформаций
  /// @param value Значение трансформации
  /// @param axis Ось
  void Change(double value, char axis);

  /// @brief Возвращает значение вектора трансформаций
  QVector3D GetChangeVector();

 private:
  GLfloat x_;  ///<
  GLfloat y_;  ///<
  GLfloat z_;  ///<
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_TRANSFORM_CLASS_H_

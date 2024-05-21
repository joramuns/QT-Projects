#ifndef CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_GLBUFFER_H_
#define CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_GLBUFFER_H_

#include <QColor>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLVertexArrayObject>

#include "transform_class.h"

namespace s21 {
/// @brief Класс служит для работы с данными 3-х мерного объекта в OpenGL
class GLBuffer : QOpenGLFunctions_4_1_Core {
 public:
  /// @brief Конструктор по умолчанию - удален
  GLBuffer() = delete;

  /// @brief Конструктор с параметрами
  /// @param vertices Данные координат 3-х мерного объекта
  /// @param program  Шейдерная программа для отрисовки
  GLBuffer(const std::vector<GLfloat> &vertices, int stride,
           QOpenGLShaderProgram *program);

  /// @brief Конструктор копирования - удален
  GLBuffer(const GLBuffer &other) = delete;

  /// @brief Конструктор копирования перемещением - удален
  GLBuffer(GLBuffer &&other) = delete;

  /// @brief Деструктор класса
  ~GLBuffer();

  /// @brief Перегрузка оператора копирования - удален
  GLBuffer &operator=(const GLBuffer &other) = delete;

  /// @brief Перегрузка оператора перемещения - удален
  GLBuffer &operator=(GLBuffer &&other) = delete;

  /// @brief Метод привязки вершинного буфера и буфера массивов  (VAO VBO)
  void Bind() const noexcept;
  void BindNormals() const noexcept;

  /// @brief Метод "отвязывающий" буферы OpenGL
  void Release() const noexcept;
  void ReleaseNormals() const noexcept;

  /// @brief Метод передающий данные 3-х мерной модели на видеокарту
  /// @param vertices отсортированный массив координат 3-х мерной модели
  void LoadData(const std::vector<GLfloat> &vertices, int stride);

  /// @brief Загрузка данных шейдера
  void LoadUniforms();

  /// @brief Возвращает размер используемых данных в VBO
  GLuint GetBuffSize() const noexcept;

  /// @brief Метод изменяющий координаты 3-х мерного объекта, имитируя вращение
  /// @param value Значение величины вращения
  /// @param axis Ось вокруг которой вращается 3-х мерный объект
  void Rotate(double value, char axis);

  /// @brief Метод изменяющий координаты 3-х мерного объекта, имитирующий
  /// перемещение
  /// @param value Значение величины перемещения
  /// @param axis Ось вдоль которой перемещаяется 3-х мерный объект
  void Move(double value, char axis);

  /// @brief Метод изменяющий координаты 3-х мерного объекта, имитирующий
  /// масштабирование
  /// @param value Значение величины масштабирования
  void Scale(double value);

 private:
  QOpenGLShaderProgram *program_;  ///< указатель на объект шейдерной программы
  QOpenGLVertexArrayObject *VAO_;  ///< указатель на объект буффера массивов
  QOpenGLBuffer *VBO_;  ///< указатель на объект буффера вершин
  QOpenGLBuffer *EBO_;  ///< указатель на объект буффера элементов

  Axes move_uniform_;    ///<
  Axes rotate_uniform_;  ///<
  Axes scale_uniform_;   ///<
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_GLBUFFER_H_

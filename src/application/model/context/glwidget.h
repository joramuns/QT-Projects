/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса GLWidget, отвечающего за работу с
данными 3-х мерного объекта в OpenGL
*/
#ifndef CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_CONTEXT_GLWIDGET_H_
#define CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_CONTEXT_GLWIDGET_H_

#include <QOpenGLWidget>

#include "../buffer/glbuffer.h"
#include "../settings_singleton.h"

namespace s21 {
/// @brief Класс GLWidget наследник QOpenGLWidget, позволяет работать с 3-х
/// мерной моделью, ее сценой в OpenGL
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core {
public:
  /// @brief Конструктор по умолчанию
  GLWidget();

  /// @brief Конструктор копирования - удален
  GLWidget(const GLWidget &other) = delete;

  /// @brief Конструктор копирования перемещением - удален
  GLWidget(GLWidget &&other) = delete;

  /// @brief Перегрузка оператора копирования - удален
  GLWidget &operator=(const GLWidget &other) = delete;

  /// @brief Перегрузка оператора перемещения - удален
  GLWidget &operator=(GLWidget &&other) = delete;

  /// @brief Деструктор класса
  ~GLWidget();

  /* Model management */

  /// @brief Метод отвечает за загрузку данных в OpenGL
  /// @param vertices  отсортированный вектор координат 3-х мерного объекта
  void LoadModel(std::vector<GLfloat> vertices);

  /// @brief Удаление/очитка данных 3-х мерного объекта по индексу
  /// @param model_number Индекс 3-х мерного объекта
  void UnloadModel(int model_number);

  /// @brief Метод отвечает за вращение 3-х мерного объекта по индексу
  /// @param value Значение величины поворота
  /// @param axis Ось вдоль которой происходит вращение
  /// @param model_number Индекс 3-х мерного объекта
  void Rotate(double value, char axis, int model_number);

  /// @brief Метод отвечает за перемещение 3-х мерного объекта по индексу
  /// @param value Значение величины перемещения
  /// @param axis Ось вдоль которой происходит перемещение
  /// @param model_number Индекс 3-х мерного объекта
  void Move(double value, char axis, int model_number);

  /// @brief Метод отвечает за масштабирование 3-х мерного объекта по индексу
  /// @param value Значение величины масштабирования
  /// @param axis Ось вдоль которой происходит масштабирования
  /// @param model_number Индекс 3-х мерного объекта
  void Scale(double value, int model_number);

  /* Scene management */

  /// @brief Метод позволяющий менять тип проекции 3-х мерного объекта
  /// @param index Тип проекции
  void SwitchProjection(int index);

  /// @brief Метод позволяющий менять тип отображения 3-х мерного объекта
  /// @param index Тип отображения
  void SwitchWireframe(int index);

  /// @brief Метод позволяющий установить цвет сцены
  /// @param color Требуемый цвет сцены
  void SetSceneColor(QColor color);

  /// @brief Метод позволяющий установить цвет вершин
  /// @param color Требуемый цвет вершин
  void SetVertexColor(QVector3D color);

  /// @brief Метод позволяющий установить цвет ребер
  /// @param color Требуемый цвет ребер
  void SetEdgeColor(QVector3D color);

  /// @brief Метод позволяющий установить тип отображения вершин
  /// @param index Тип отображения вершин
  void SetVertexOption(int index);

  /// @brief Метод позволяющий установить тип отображения ребер
  /// @param index Тип отображения ребер
  void SetEdgeOption(int index);

  /// @brief Метод позволяющий установить значение отображаемого размера вершин
  /// @param value Значение величины отображаемых вершин
  void SetVertexSize(double value);

  /// @brief Метод  позволяющий установить значения отображаемого размера ребер
  /// @param value Значение величины отображаемых ребер
  void SetEdgeSize(double value);

protected:
  /// @brief Метод произовдит инициализацию OpenGL функций
  void initializeGL() override;

  /// @brief Метод отвечает за изменение окна виджета OpenGL
  /// @param w ширина в пикселях
  /// @param h высота в пикселях
  void resizeGL(int w, int h) override;

  /// @brief
  void paintGL() override;

private:
  /// @brief Метод отвечающий за загрузку шейдеров
  void LoadShaders();

  /// @brief Метод отвечающий за загрузку сцены
  void SceneLoader();

  /// @brief Метод отвечающий за загрузку данных 3-х мерного объекта в OpenGL
  void ModelLoader();

  /// @brief Загрузка общих данных в шейдеры
  void LoadCommonUniforms();

private:
  QOpenGLShaderProgram *program_; ///< Указатель на объект шейдерной программы
  std::vector<GLBuffer *> GLBuffers_; ///<

  SettingsSingleton &settings_;
  // temp settings
  QColor bg_color_;         ///< цвет сцены
  QVector3D vert_color_;    ///< цвет вершин
  QVector3D edge_color_;    ///< цвет ребер
  bool central_projection_; ///< тип проекции
  bool solid_;              ///< тип отображения
  int vert_type_;           ///< тип отображения вершин
  GLfloat vert_size_; ///< значение величины отображаемых вершин
  GLfloat edge_size_; ///< значение величины отображаемых ребер
  bool dashed_lines_; ///< тип отображения ребер
};
} // namespace s21

#endif // CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_CONTEXT_GLWIDGET_H_

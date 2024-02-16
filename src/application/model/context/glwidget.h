/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса GLWidget, отвечающего за работу с
данными 3-х мерного объекта в OpenGL
*/
#ifndef CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_CONTEXT_GLWIDGET_H_
#define CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_CONTEXT_GLWIDGET_H_
#define kGifFrameNumber 50

#include <QOpenGLWidget>
#include <QTimer>

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

  void SaveScreenshot(const QString &filename);

  void SaveGif(const QString &filename);

  /* Scene management */

  /// @brief Метод позволяющий менять тип проекции 3-х мерного объекта
  /// @param index Тип проекции
  inline void SwitchProjection(int index) {
    settings_.SetProjectionType(index);
  }

  /// @brief Метод позволяющий менять тип отображения 3-х мерного объекта
  /// @param index Тип отображения
  inline void SwitchWireframe(int index) { settings_.SetPolygonType(index); }

  /// @brief Метод позволяющий установить цвет сцены
  /// @param color Требуемый цвет сцены
  inline void SetSceneColor(QColor color) { settings_.SetBGColor(color); }

  /// @brief Метод позволяющий установить цвет вершин
  /// @param color Требуемый цвет вершин
  inline void SetVertexColor(QVector3D color) {
    settings_.SetVertexColor(color);
  }

  /// @brief Метод позволяющий установить цвет ребер
  /// @param color Требуемый цвет ребер
  inline void SetEdgeColor(QVector3D color) { settings_.SetEdgeColor(color); }

  /// @brief Метод позволяющий установить тип отображения вершин
  /// @param index Тип отображения вершин
  inline void SetVertexOption(int index) { settings_.SetVertexType(index); }

  /// @brief Метод позволяющий установить тип отображения ребер
  /// @param index Тип отображения ребер
  inline void SetEdgeOption(int index) {
    settings_.SetEdgeType(static_cast<bool>(index));
  }

  /// @brief Метод позволяющий установить значение отображаемого размера вершин
  /// @param value Значение величины отображаемых вершин
  inline void SetEdgeSize(double value) {
    settings_.SetEdgeSize(static_cast<GLfloat>(value));
  }

  /// @brief Метод  позволяющий установить значения отображаемого размера ребер
  /// @param value Значение величины отображаемых ребер
  inline void SetVertexSize(double value) {
    settings_.SetVertexSize(static_cast<GLfloat>(value));
  }

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

  void GifFrameGrabber();



 private:
  QOpenGLShaderProgram *program_;  ///< Указатель на объект шейдерной программы
  std::vector<GLBuffer *> GLBuffers_;  ///<

  SettingsSingleton &settings_;

  // TEMP
  std::vector<QImage> gif_frames_;
  QTimer timer_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_CONTEXT_GLWIDGET_H_

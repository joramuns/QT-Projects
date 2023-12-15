#ifndef VIEW_OPENGL_GLWIDGET_H_
#define VIEW_OPENGL_GLWIDGET_H_

#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "transform_class.h"

namespace s21 {
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core {
 public:
  GLWidget();
  ~GLWidget();

  void LoadModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
  void UnloadModel(int model_number);
  void Rotate(double value, char axis, int model_number);
  void Move(double value, char axis, int model_number);
  void Scale(double value, int model_number);

 protected:
  /* void initializeGL() override; */
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void LoadShaders();
  void LoadUniforms(int model_number);

 private:
  QOpenGLShaderProgram *program_;
  std::vector<QOpenGLVertexArrayObject *> VAO_vector_;
  std::vector<QOpenGLBuffer *> VBO_vector_;
  std::vector<QOpenGLBuffer *> EBO_vector_;

  std::vector<Axes> move_uniform_;
  std::vector<Axes> rotate_uniform_;
  std::vector<Axes> scale_uniform_;
};
}  // namespace s21
#endif  // VIEW_OPENGL_GLWIDGET_H_

#ifndef VIEW_OPENGL_GLWIDGET_H_
#define VIEW_OPENGL_GLWIDGET_H_

#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

namespace s21 {
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core {
 public:
  GLWidget();
  ~GLWidget();

  void Render(QOpenGLVertexArrayObject *VAO);
  void LoadModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices);

 protected:
  /* void initializeGL() override; */
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  QOpenGLShaderProgram *program_;
  QOpenGLVertexArrayObject VAO_;
  QOpenGLVertexArrayObject VAO2_;
  QOpenGLBuffer VBO_;
  QOpenGLBuffer VBO2_;
  QOpenGLBuffer EBO_;

  std::vector<QOpenGLVertexArrayObject *> VAO_vector_;
  std::vector<QOpenGLBuffer *> VBO_vector_;
  std::vector<QOpenGLBuffer *> EBO_vector_;
};
}  // namespace s21
#endif  // VIEW_OPENGL_GLWIDGET_H_

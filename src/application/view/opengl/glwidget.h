#ifndef VIEW_OPENGL_GLWIDGET_H_
#define VIEW_OPENGL_GLWIDGET_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

namespace s21 {
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  GLWidget();

 protected:
  /* void initializeGL() override; */
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  QOpenGLShaderProgram program;
  GLuint VBO;
};
}  // namespace s21
#endif  // VIEW_OPENGL_GLWIDGET_H_

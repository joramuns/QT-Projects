#ifndef VIEW_OPENGL_GLWIDGET_H_
#define VIEW_OPENGL_GLWIDGET_H_
#include <OpenGL/gl.h>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include <iostream>
namespace s21 {
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core {
 public:
  GLWidget();
  ~GLWidget();


 protected:
  /* void initializeGL() override; */
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  // QOpenGLShaderProgram *program_;
  // QOpenGLVertexArrayObject VAO_;
  // QOpenGLVertexArrayObject VAO2_;
  GLuint VAO_;
  GLuint VBO_;
  GLuint shader_program_;
  // QOpenGLBuffer VBO_;
  // QOpenGLBuffer VBO2_;
  // QOpenGLBuffer EBO_;
};
}  // namespace s21
#endif  // VIEW_OPENGL_GLWIDGET_H_

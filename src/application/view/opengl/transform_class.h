#ifndef VIEW_OPENGL_TRANSFORM_CLASS_H_
#define VIEW_OPENGL_TRANSFORM_CLASS_H_

#include <QOpenGLShaderProgram>

namespace s21 {
class Axes {
 public:
  Axes() = delete;
  explicit Axes(double init);
  void Change(double value, char axis);
  QVector3D GetChangeVector();

 private:
  GLfloat x_;
  GLfloat y_;
  GLfloat z_;
};
}  // namespace s21
#endif  // VIEW_OPENGL_TRANSFORM_CLASS_H_

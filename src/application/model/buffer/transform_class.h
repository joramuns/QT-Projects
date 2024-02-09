#ifndef CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_TRANSFORM_CLASS_H_
#define CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_TRANSFORM_CLASS_H_

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
#endif  // CPP4_3DVIEWER_V2_0_2_APPLICATION_MODEL_BUFFER_TRANSFORM_CLASS_H_

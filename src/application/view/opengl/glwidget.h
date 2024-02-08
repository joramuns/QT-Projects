#ifndef VIEW_OPENGL_GLWIDGET_H_
#define VIEW_OPENGL_GLWIDGET_H_


#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "transform_class.h"
#include "glbuffer.h"

namespace s21 {
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core {
 public:
  GLWidget();
  ~GLWidget();

  void LoadModel(std::vector<GLfloat> vertices);
  void UnloadModel(int model_number);
  void Rotate(double value, char axis, int model_number);
  void Move(double value, char axis, int model_number);
  void Scale(double value, int model_number);
  void SwitchProjection(int index);
  void SwitchWireframe(int index);
  void SetSceneColor(QColor color);
  void SetVertexColor(QVector3D color);
  void SetEdgeColor(QVector3D color);
  void SetVertexOption(int index);
  void SetEdgeOption(int index);
  void SetVertexSize(double value);
  void SetEdgeSize(double value);

 protected:
  /* void initializeGL() override; */
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void LoadShaders();
  void LoadCommonUniforms();

 private:
  QOpenGLShaderProgram *program_;
  std::vector<GLBuffer *> GLBuffers_;

  // temp settings
  QColor bg_color_;
  QVector3D vert_color_;
  QVector3D edge_color_;
  bool central_projection_;
  bool solid_;
  int vert_type_;
  GLfloat vert_size_;
  GLfloat edge_size_;
  bool dashed_lines_;
};
}  // namespace s21

#endif  // VIEW_OPENGL_GLWIDGET_H_

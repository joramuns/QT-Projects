#ifndef VIEW_OPENGL_GLBUFFER_H_
#define VIEW_OPENGL_GLBUFFER_H_

#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "transform_class.h"

namespace s21 {
class GLBuffer : QOpenGLFunctions_4_1_Core {
 public:
  GLBuffer();
  GLBuffer(const std::vector<GLfloat> &vertices,
           const std::vector<GLuint> &indices, QOpenGLShaderProgram *program);
  GLBuffer(const GLBuffer &other) = delete;
  GLBuffer(GLBuffer &&other) = delete;
  ~GLBuffer();

  GLBuffer &operator=(const GLBuffer &other) = delete;
  GLBuffer &operator=(GLBuffer &&other) = delete;

  void Bind() const noexcept;
  void Release() const noexcept;
  void LoadData(const std::vector<GLfloat> &vertices,
                const std::vector<GLuint> &indices);
  void LoadUniforms();
  GLuint GetBuffSize() const noexcept;
  void Rotate(double value, char axis);
  void Move(double value, char axis);
  void Scale(double value);

 private:
  QOpenGLShaderProgram *program_;
  QOpenGLVertexArrayObject *VAO_;
  QOpenGLBuffer *VBO_;
  QOpenGLBuffer *EBO_;
  
  Axes move_uniform_;
  Axes rotate_uniform_;
  Axes scale_uniform_;
};
}  // namespace s21

#endif  // VIEW_OPENGL_GLBUFFER_H_

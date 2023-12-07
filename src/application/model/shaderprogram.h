#ifndef MODEL_SHADERPROGRAM_H_
#define MODEL_SHADERPROGRAM_H_

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

namespace s21 {
class ShaderProgram {
 public:
  ShaderProgram() = delete;
  ShaderProgram(const std::vector<GLfloat> &vertices,
                const std::vector<GLuint> &indices);
  ShaderProgram(const ShaderProgram &other) = delete;
  ShaderProgram(ShaderProgram &&other) = delete;
  ~ShaderProgram();

  ShaderProgram &operator=(const ShaderProgram &other) = delete;
  ShaderProgram &operator=(ShaderProgram &&other) = delete;

  QOpenGLShaderProgram *GetProgram();
  QOpenGLVertexArrayObject *GetVAO();

 private:
  void CreateProgram();
  void CreateBuffer(const std::vector<GLfloat> &vertices,
                    const std::vector<GLuint> &indices);

 private:
  QOpenGLShaderProgram *program_;
  QOpenGLVertexArrayObject *VAO_;
  QOpenGLBuffer VBO_;
  QOpenGLBuffer EBO_;
};
}  // namespace s21

#endif  // MODEL_SHADERPROGRAM_H_

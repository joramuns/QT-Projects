#ifndef MODEL_SHADERPROGRAM_H_
#define MODEL_SHADERPROGRAM_H_

#include <QOpenGLShaderProgram>

namespace s21 {
class ShaderProgram {
  ShaderProgram();
  ~ShaderProgram();

  QOpenGLShaderProgram *GetProgram();

 private:
  QOpenGLShaderProgram *program_;
};
}  // namespace s21

#endif  // MODEL_SHADERPROGRAM_H_

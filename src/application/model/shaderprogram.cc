#include "shaderprogram.h"

namespace s21 {

ShaderProgram::ShaderProgram() {}
ShaderProgram::~ShaderProgram() {
  delete program_;
}

QOpenGLShaderProgram *ShaderProgram::GetProgram() {
  /* program_ = new QOpenGLShaderProgram(); */
  /* if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/v_shader")) */
  /*   qDebug() << "Vertex shader errors:\n" << program_->log(); */

  /* if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/f_shader")) */
  /*   qDebug() << "Fragment shader errors:\n" << program_->log(); */

  /* if (!program_->link()) */
  /*   qDebug() << "Shader linker errors:\n" << program_->log(); */

  /* std::vector<GLfloat> vertices1{ */
  /*     0.5f,  0.5f,  0.0f,  // Верхний правый угол */
  /*     0.5f,  -0.5f, 0.0f,  // Нижний правый угол */
  /*     -0.5f, -0.5f, 0.0f,  // Нижний левый угол */
  /*     -0.5f, 0.5f,  0.0f   // Верхний левый угол */
  /* }; */

  /* std::vector<GLfloat> vertices2{ */
  /*     0.999999,  -0.999999, -0.999999,  // */
  /*     0.999999,  -0.999999, 0.999999,   // */
  /*     -0.999999, -0.999999, 0.999999,   // */
  /*     -0.999999, -0.999999, -0.999999,  // */
  /*     0.999999,  0.999999,  -0.999999,  // */
  /*     0.999999,  0.999999,  0.999999,   // */
  /*     -0.999999, 0.999999,  0.999999,   // */
  /*     -0.999999, 0.999999,  -0.999999   // */

  /* }; */

  /* std::vector<GLuint> indices1{0, 1, 3}; */
  /* std::vector<GLuint> indices2{ */
  /*     2, 3, 4, 8, 7, 6,  // */
  /*     5, 6, 2,           // */
  /*     6, 7, 3,           // */
  /*     3, 7, 8,           // */
  /*     1, 4, 8,           // */
  /*     1, 2, 4,           // */
  /*     5, 8, 6,           // */
  /*     1, 5, 2,           // */
  /*     2, 6, 3,           // */
  /*     4, 3, 8,           // */
  /*     5, 1, 8            // */
  /* }; */

  /* VAO_.create(); */
  /* VAO_.bind(); */

  /* VBO_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); */
  /* VBO_.create(); */
  /* VBO_.setUsagePattern(QOpenGLBuffer::StaticDraw); */
  /* VBO_.bind(); */
  /* VBO_.allocate(vertices1.data(), vertices1.size() * sizeof(GLfloat)); */

  /* EBO_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); */
  /* EBO_.create(); */
  /* EBO_.setUsagePattern(QOpenGLBuffer::StaticDraw); */
  /* EBO_.bind(); */
  /* EBO_.allocate(indices1.data(), indices1.size() * sizeof(GLuint)); */

  /* program_->enableAttributeArray(0); */
  /* program_->setAttributeBuffer(0, GL_FLOAT, 0, 3); */

  /* VBO_.release(); */
  /* VAO_.release(); */

  /* VAO2_.create(); */
  /* VAO2_.bind(); */

  /* VBO2_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); */
  /* VBO2_.create(); */
  /* VBO2_.setUsagePattern(QOpenGLBuffer::StaticDraw); */
  /* VBO2_.bind(); */
  /* VBO2_.allocate(vertices2.data(), vertices2.size() * sizeof(GLfloat)); */

  /* EBO_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); */
  /* EBO_.create(); */
  /* EBO_.setUsagePattern(QOpenGLBuffer::StaticDraw); */
  /* EBO_.bind(); */
  /* EBO_.allocate(indices2.data(), indices2.size() * sizeof(GLuint)); */

  /* program_->enableAttributeArray(0); */
  /* program_->setAttributeBuffer(0, GL_FLOAT, 0, 3); */

  /* VBO2_.release(); */
  /* VAO2_.release(); */
  return program_;
}
}  // namespace s21

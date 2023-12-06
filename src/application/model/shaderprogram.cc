#include "shaderprogram.h"

// TEMP
#include <iostream>

namespace s21 {

ShaderProgram::ShaderProgram(const std::vector<GLfloat> &vertices,
                             const std::vector<GLuint> &indices) {
  CreateProgram();
  CreateBuffer(vertices, indices);
}

ShaderProgram::~ShaderProgram() {
  VAO_->destroy();
  VBO_.destroy();
  EBO_.destroy();
  program_->disableAttributeArray(0);
  program_->release();
  delete program_;
}

QOpenGLShaderProgram *ShaderProgram::GetProgram() { return program_; }

QOpenGLVertexArrayObject *ShaderProgram::GetVAO() { return VAO_; }

void ShaderProgram::CreateProgram() {
  program_ = new QOpenGLShaderProgram();
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/v_shader"))
    qDebug() << "Vertex shader errors:\n" << program_->log();

  if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/f_shader"))
    qDebug() << "Fragment shader errors:\n" << program_->log();

  if (!program_->link())
    qDebug() << "Shader linker errors:\n" << program_->log();
}

void ShaderProgram::CreateBuffer(const std::vector<GLfloat> &vertices,
                                 const std::vector<GLuint> &indices) {
  (void)vertices;
  (void)indices;
  /* program_->bind(); */
  /* VAO_->create(); */
  /* VAO_->bind(); */

  /* VBO_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); */
  /* VBO_.create(); */
  /* VBO_.setUsagePattern(QOpenGLBuffer::StaticDraw); */
  /* VBO_.bind(); */
  /* VBO_.allocate(vertices.data(), vertices.size() * sizeof(GLfloat)); */

  /* EBO_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); */
  /* EBO_.create(); */
  /* EBO_.setUsagePattern(QOpenGLBuffer::StaticDraw); */
  /* EBO_.bind(); */
  /* EBO_.allocate(indices.data(), indices.size() * sizeof(GLuint)); */

  /* program_->enableAttributeArray(0); */
  /* program_->setAttributeBuffer(0, GL_FLOAT, 0, 3); */

  /* // UNIFORMS */
  /* const QVector4D color{1.0f, 1.0f, 0.2f, 1.0f}; */
  /* program_->setUniformValue("ourColor", color); */

  /* GLfloat x_move{-0.25f}, y_move{-0.25f}, z_move{0.0f}; */
  /* QVector3D translate_vector{x_move, y_move, z_move}; */
  /* program_->setUniformValue("translateVector", translate_vector); */

  /* GLfloat x_rotate{0.0f}, y_rotate{0.0f}, z_rotate{0.0f}; */
  /* QVector3D rotate_vector{x_rotate, y_rotate, z_rotate}; */
  /* program_->setUniformValue("rotateVector", rotate_vector); */
  /* // UNIFORMS */

  /* VBO_.release(); */
  /* VAO_->release(); */
}
}  // namespace s21

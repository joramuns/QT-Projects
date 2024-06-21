#include "glbuffer.h"

#include <iostream>

namespace s21 {
GLBuffer::GLBuffer(const std::vector<GLfloat> &vertices, int stride,
                   QOpenGLShaderProgram *program)
    : program_(program),
      VAO_(new QOpenGLVertexArrayObject),
      VBO_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
      move_uniform_{0.0},
      rotate_uniform_{0.0},
      scale_uniform_{1.0} {
  initializeOpenGLFunctions();
  VBO_->setUsagePattern(QOpenGLBuffer::DynamicDraw);
  if (!program->bind()) qDebug() << "Program failure:\n" << program->log();
  LoadData(vertices, stride);
  Release();
}

GLBuffer::~GLBuffer() {
  VAO_->destroy();
  VBO_->destroy();
  delete VAO_;
  delete VBO_;
}

void GLBuffer::Bind() const noexcept {
  VAO_->bind();
  VBO_->bind();
}

void GLBuffer::Release() const noexcept {
  VAO_->release();
  VBO_->release();
}

void GLBuffer::LoadData(const std::vector<GLfloat> &vertices, int stride) {
  initializeOpenGLFunctions();
  VAO_->create();
  VBO_->create();

  Bind();
  VBO_->allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
  std::cout << "load data " << vertices.size() << std::endl;
  glEnableVertexAttribArray(0);
  std::cout << stride << std::endl;
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * stride,
                        (void *)0);
  if (stride - 6 == 3 || stride - 4 == 3) {
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * stride,
                          (void *)(4 * sizeof(GLfloat)));
  }
  if (stride - 7 == 2 || stride - 4 == 2) {
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * stride,
                          (void *)((stride - 2) * sizeof(GLfloat)));
  }
  Release();
}

void GLBuffer::LoadUniforms() {
  const QVector3D light_color{1.0f, 1.0f, 1.0f};
  program_->setUniformValue("lightColor", light_color);

  program_->setUniformValue("translateVector", move_uniform_.GetChangeVector());

  program_->setUniformValue("rotateVector", rotate_uniform_.GetChangeVector());

  program_->setUniformValue("scaleVector", scale_uniform_.GetChangeVector());

  program_->setUniformValue("gapSize",
                            10 * scale_uniform_.GetChangeVector()[0]);
  program_->setUniformValue("dashSize",
                            10 * scale_uniform_.GetChangeVector()[0]);
}

GLuint GLBuffer::GetBuffSize() const noexcept {
  return VBO_->size() / sizeof(GLfloat) * 9;
}

void GLBuffer::Rotate(double value, char axis) {
  rotate_uniform_.Change(value, axis);
}

void GLBuffer::Move(double value, char axis) {
  move_uniform_.Change(value, axis);
}

void GLBuffer::Scale(double value) { scale_uniform_.Change(value, 'A'); }
}  // namespace s21

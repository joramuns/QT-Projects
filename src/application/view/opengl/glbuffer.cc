#include "glbuffer.h"

namespace s21 {
GLBuffer::GLBuffer()
    : move_uniform_{0.0}, rotate_uniform_{0.0}, scale_uniform_{1.0} {
  initializeOpenGLFunctions();
  VAO_ = new QOpenGLVertexArrayObject;

  VBO_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

  VBO_->setUsagePattern(QOpenGLBuffer::DynamicDraw);

  // EBO_ = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

  // EBO_->setUsagePattern(QOpenGLBuffer::DynamicDraw);
}

GLBuffer::GLBuffer(const std::vector<GLfloat> &vertices,
                   QOpenGLShaderProgram *program)
    : GLBuffer() {
  program_ = program;
  if (!program->bind())
    qDebug() << "Program failure:\n" << program->log();
  LoadData(vertices);
  Release();
  program->release();
}

GLBuffer::~GLBuffer() {
  VAO_->destroy();
  VBO_->destroy();
  // EBO_->destroy();
  delete VAO_;
  delete VBO_;
  // delete EBO_;
  // VBO_normals_->destroy();
  // EBO_normals_->destroy();
  // delete VBO_normals_;
  // delete EBO_normals_;
}

void GLBuffer::Bind() const noexcept {
  VAO_->bind();
  VBO_->bind();
}

void GLBuffer::Release() const noexcept {
  VAO_->release();
  VBO_->release();
}

void GLBuffer::LoadData(const std::vector<GLfloat> &vertices) {
  initializeOpenGLFunctions();
  VAO_->create();
  VBO_->create();

  Bind();
  VBO_->allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9,
                        (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9,
                        (void *)(4 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9,
                        (void *)(7 * sizeof(GLfloat)));
  // Release();
}

void GLBuffer::LoadUniforms() {
  const QVector3D light_color{1.0f, 1.0f, 1.0f};
  const QVector3D model_color{0.85f, 0.85f, 0.85f};
  program_->setUniformValue("modelColor", model_color);
  program_->setUniformValue("lightColor", light_color);

  program_->setUniformValue("translateVector", move_uniform_.GetChangeVector());

  program_->setUniformValue("rotateVector", rotate_uniform_.GetChangeVector());

  program_->setUniformValue("scaleVector", scale_uniform_.GetChangeVector());

  QMatrix4x4 perspective_matrix{};
  perspective_matrix.perspective(30.0, 1.0, 0.1, 90.0);
  perspective_matrix.translate(-0.0, -0.0, -2.0);
  program_->setUniformValue("perspectiveMatrix", perspective_matrix);
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
} // namespace s21

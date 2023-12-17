#include "glbuffer.h"

namespace s21 {
GLBuffer::GLBuffer() : move_uniform_{0.0}, rotate_uniform_{0.0}, scale_uniform_{1.0} {
  initializeOpenGLFunctions();
  VAO_ = new QOpenGLVertexArrayObject;

  VBO_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  VBO_normals_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

  VBO_->setUsagePattern(QOpenGLBuffer::DynamicDraw);
  VBO_normals_->setUsagePattern(QOpenGLBuffer::DynamicDraw);

  EBO_ = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  EBO_normals_ = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

  EBO_->setUsagePattern(QOpenGLBuffer::DynamicDraw);
  EBO_normals_->setUsagePattern(QOpenGLBuffer::DynamicDraw);
}

GLBuffer::GLBuffer(const std::vector<GLfloat> &vertices,
                   const std::vector<GLuint> &indices,
                   const std::vector<GLfloat> &normals,
                   const std::vector<GLuint> &normal_indices,
                   QOpenGLShaderProgram *program)
    : GLBuffer() {
  program_ = program;
  if (!program->bind()) qDebug() << "Program failure:\n" << program->log();
  LoadData(vertices, indices, normals, normal_indices);
  Release();
  program->release();
}

GLBuffer::~GLBuffer() {
  VAO_->destroy();
  VBO_->destroy();
  EBO_->destroy();
  delete VAO_;
  delete VBO_;
  delete EBO_;
  VBO_normals_->destroy();
  EBO_normals_->destroy();
  delete VBO_normals_;
  delete EBO_normals_;
}

void GLBuffer::Bind() const noexcept {
  VAO_->bind();

}

void GLBuffer::BindNormals() const noexcept {
  VBO_normals_->bind();
  EBO_normals_->bind();
}

void GLBuffer::Release() const noexcept {
  VAO_->release();
}

void GLBuffer::ReleaseNormals() const noexcept {
  VBO_normals_->release();
  EBO_normals_->release();
}

void GLBuffer::LoadData(const std::vector<GLfloat> &vertices,
           const std::vector<GLuint> &vertex_indices, const std::vector<GLfloat> &normals, const std::vector<GLuint> &normal_indices) {
  initializeOpenGLFunctions();
  VAO_->create();
  VBO_->create();
  EBO_->create();
  VBO_normals_->create();
  EBO_normals_->create();

  Bind();
  VBO_->bind();
  EBO_->bind();
  VBO_->allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
  EBO_->allocate(vertex_indices.data(), vertex_indices.size() * sizeof(GLuint));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)0);
  VBO_->release();
  EBO_->release();
  BindNormals();
  VBO_normals_->allocate(normals.data(), normals.size() * sizeof(GLfloat));
  EBO_normals_->allocate(normal_indices.data(), normal_indices.size() * sizeof(GLuint));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void *)0);

  ReleaseNormals();
  Release();
}

void GLBuffer::LoadUniforms() {
  const QVector4D light_color{1.0f, 1.0f, 1.0f, 1.0f};
  const QVector4D model_color{1.0f, 0.4f, 0.6f, 1.0f};
  program_->setUniformValue("modelColor", model_color);
  program_->setUniformValue("lightColor", light_color);

  program_->setUniformValue("translateVector",
                            move_uniform_.GetChangeVector());

  program_->setUniformValue("rotateVector",
                            rotate_uniform_.GetChangeVector());

  program_->setUniformValue("scaleVector",
                            scale_uniform_.GetChangeVector());

  QMatrix4x4 perspective_matrix{};
  perspective_matrix.perspective(30.0, 1.0, 0.1, 90.0);
  perspective_matrix.translate(-0.0, -0.0, -2.0);
  program_->setUniformValue("perspectiveMatrix", perspective_matrix);
}

GLuint GLBuffer::GetBuffSize() const noexcept {
  return EBO_->size() / sizeof(GLuint);
}

void GLBuffer::Rotate(double value, char axis) {
  rotate_uniform_.Change(value, axis);
}

void GLBuffer::Move(double value, char axis) {
  move_uniform_.Change(value, axis);
}

void GLBuffer::Scale(double value) {
  scale_uniform_.Change(value, 'A');
}
}  // namespace s21

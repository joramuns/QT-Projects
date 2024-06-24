#include "glbuffer2.h"

namespace s21 {
GLBuffer2::GLBuffer2(const std::vector<Vertex> &vertices,
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
  LoadData(vertices);
  Release();
}

GLBuffer2::~GLBuffer2() {
  VAO_->destroy();
  VBO_->destroy();
  delete VAO_;
  delete VBO_;
}

void GLBuffer2::Bind() const noexcept {
  VAO_->bind();
  VBO_->bind();
}

void GLBuffer2::Release() const noexcept {
  VAO_->release();
  VBO_->release();
}

void GLBuffer2::LoadData(const std::vector<Vertex> &vertices) {
  initializeOpenGLFunctions();
  VAO_->create();
  VBO_->create();
  Bind();

  VBO_->allocate(vertices.data(), vertices.size() * sizeof(Vertex));

  int posLoc = program_->attributeLocation("position");
  program_->enableAttributeArray(posLoc);
  program_->setAttributeBuffer(posLoc, GL_FLOAT, offsetof(Vertex, position), 3,
                               sizeof(Vertex));

  int normalLoc = program_->attributeLocation("normal");
  program_->enableAttributeArray(normalLoc);
  program_->setAttributeBuffer(normalLoc, GL_FLOAT, offsetof(Vertex, normal), 3,
                               sizeof(Vertex));

  int texCoordLoc = program_->attributeLocation("texCoord");
  program_->enableAttributeArray(texCoordLoc);
  program_->setAttributeBuffer(texCoordLoc, GL_FLOAT,
                               offsetof(Vertex, texCoord), 2, sizeof(Vertex));

  Release();
}

void GLBuffer2::LoadUniforms() {
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

GLuint GLBuffer2::GetBuffSize() const noexcept {
  return VBO_->size() / sizeof(GLfloat) * 9;
}

void GLBuffer2::Rotate(double value, char axis) {
  rotate_uniform_.Change(value, axis);
}

void GLBuffer2::Move(double value, char axis) {
  move_uniform_.Change(value, axis);
}

void GLBuffer2::Scale(double value) { scale_uniform_.Change(value, 'A'); }
}  // namespace s21

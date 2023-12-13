#define GL_SILENCE_DEPRECATION

#include "glwidget.h"

#include <QDebug>
/* #include <QFile> */
#include <iostream>
#include <vector>

namespace s21 {
GLWidget::GLWidget() : move_uniform_(0.0f), rotate_uniform_(0.0f), scale_uniform_(1.0f) {
  /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); */
  setMinimumWidth(660);
}

GLWidget::~GLWidget() {
  makeCurrent();
  for (std::size_t i = 0; i < VAO_vector_.size(); i++) {
    VAO_vector_[i]->destroy();
    VBO_vector_[i]->destroy();
    EBO_vector_[i]->destroy();
    delete VAO_vector_[i];
    delete VBO_vector_[i];
    delete EBO_vector_[i];
  }
  program_->disableAttributeArray(0);
  program_->release();
  delete program_;
}

void GLWidget::LoadModel(std::vector<GLfloat> vertices,
                         std::vector<GLuint> indices) {
  auto VAO_current = VAO_vector_.emplace_back(new QOpenGLVertexArrayObject{});
  VAO_current->create();
  VAO_current->bind();

  auto VBO_current =
      VBO_vector_.emplace_back(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
  VBO_current->create();
  VBO_current->setUsagePattern(QOpenGLBuffer::DynamicDraw);

  auto EBO_current =
      EBO_vector_.emplace_back(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
  EBO_current->create();
  EBO_current->setUsagePattern(QOpenGLBuffer::DynamicDraw);

  VAO_current->bind();
  VBO_current->bind();
  EBO_current->bind();

  VBO_current->allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
  EBO_current->allocate(indices.data(), indices.size() * sizeof(GLuint));

  program_->enableAttributeArray(0);
  program_->setAttributeBuffer(0, GL_FLOAT, 0, 4);

  VBO_current->release();
  VAO_current->release();

  EBO_current->release();
  update();
}

void GLWidget::Rotate(double value, char axis) {
  rotate_uniform_.Change(value, axis);
}

void GLWidget::Move(double value, char axis) {
  move_uniform_.Change(value, axis);
}

void GLWidget::Scale(double value) { scale_uniform_.Change(value, 'A'); }

void GLWidget::initializeGL() {
  // Set up the rendering context, load shaders and other resources, etc.:
  LoadShaders();
  initializeOpenGLFunctions();
}

void GLWidget::resizeGL(int w, int h) {
  // Update projection matrix and other size related settings:
  (void)w;
  (void)h;
  /* m_projection.setToIdentity(); */
  /* m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f); */
}

void GLWidget::paintGL() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  /* const qreal retinaScale = devicePixelRatio(); */
  /* glViewport(0, 0, width() * retinaScale, height() * retinaScale); */
  // Draw the scene:
  glClearColor(0.2, 0.1, 0.1, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  program_->bind();
  LoadUniforms();

  for (std::size_t i = 0; i < VAO_vector_.size(); i++) {
    VAO_vector_[i]->bind();
    glDrawElements(GL_TRIANGLES, EBO_vector_[i]->size() / sizeof(GLuint),
                   GL_UNSIGNED_INT, 0);
    VAO_vector_[i]->release();
  }
}

void GLWidget::LoadShaders() {
  program_ = new QOpenGLShaderProgram();
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/v_shader"))
    qDebug() << "Vertex shader errors:\n" << program_->log();

  if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/f_shader"))
    qDebug() << "Fragment shader errors:\n" << program_->log();

  if (!program_->link())
    qDebug() << "Shader linker errors:\n" << program_->log();
}

void GLWidget::LoadUniforms() {
  const QVector4D color{1.0f, 1.0f, 0.2f, 1.0f};
  program_->setUniformValue("ourColor", color);

  /* GLfloat x_move{-0.25f}, y_move{-0.25f}, z_move{0.0f}; */
  /* QVector3D translate_vector{x_move, y_move, z_move}; */
  program_->setUniformValue("translateVector", move_uniform_.GetChangeVector());

  /* GLfloat x_rotate{0.0f}, y_rotate{0.0f}, z_rotate{0.0f}; */
  /* QVector3D rotate_vector{x_rotate, y_rotate, z_rotate}; */
  program_->setUniformValue("rotateVector", rotate_uniform_.GetChangeVector());

  program_->setUniformValue("scaleVector", scale_uniform_.GetChangeVector());

  QMatrix4x4 perspective_matrix{};
  perspective_matrix.perspective(30.0, 1.0, 0.1, 90.0);
  perspective_matrix.translate(-0.0, -0.0, -2.0);
  program_->setUniformValue("perspectiveMatrix", perspective_matrix);
}

}  // namespace s21

#define GL_SILENCE_DEPRECATION

#include "glwidget.h"

#include <QDebug>
/* #include <QFile> */
#include <vector>

namespace s21 {
GLWidget::GLWidget() {
  /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); */
  setMinimumWidth(660);
}

GLWidget::~GLWidget() {
  /* VAO_.destroy(); */
  /* VBO_.destroy(); */
  delete program_;
}

void GLWidget::initializeGL() {
  // Set up the rendering context, load shaders and other resources, etc.:
  initializeOpenGLFunctions();

  program_ = new QOpenGLShaderProgram();
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/v_shader"))
    qDebug() << "Vertex shader errors:\n" << program_->log();

  if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/f_shader"))
    qDebug() << "Fragment shader errors:\n" << program_->log();

  if (!program_->link())
    qDebug() << "Shader linker errors:\n" << program_->log();

  /* GLfloat vertices[] = {-0.5f, -0.5f, -0.3f, 0.5f, -0.5f, */
  /*                       0.0f,  0.0f,  0.5f,  0.0f}; */

  std::vector<GLfloat> vertices{
      0.5f,  0.5f,  0.0f,  // Верхний правый угол
      0.5f,  -0.5f, 0.0f,  // Нижний правый угол
      -0.5f, -0.5f, 0.0f,  // Нижний левый угол
      -0.5f, 0.5f,  0.0f   // Верхний левый угол
  };

  /* GLuint indices[] = {0, 1, 3, 1, 2, 3}; */
  /* GLuint indices[] = {0, 1, 3, 0, 3, 2}; */
  std::vector<GLuint> indices{0, 1, 3, 0, 3, 2};

  /* 0 1 3 2 4 2 1 */
  /*   0 1 3 */
  /*   0 3 2 */
  /*   0 2 4 */
  /*   0 4 2 */
  /*   0 2 1 */

  VAO_.create();
  VAO_.bind();

  VBO_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  VBO_.create();
  VBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  VBO_.bind();
  VBO_.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));

  EBO_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  EBO_.create();
  EBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  EBO_.bind();
  EBO_.allocate(indices.data(), indices.size() * sizeof(GLuint));

  program_->enableAttributeArray(0);
  program_->setAttributeBuffer(0, GL_FLOAT, 0, 3);

  VBO_.release();
  VAO_.release();
}

void GLWidget::resizeGL(int w, int h) {
  // Update projection matrix and other size related settings:
  (void)w;
  (void)h;
  /* m_projection.setToIdentity(); */
  /* m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f); */
}

void GLWidget::paintGL() {
  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  // Draw the scene:
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  program_->bind();
  VAO_.bind();

  /* glPointSize(9); */
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  /* glDrawArrays(GL_POINTS, 0, 9); */
  VAO_.release();

  program_->release();
}
}  // namespace s21

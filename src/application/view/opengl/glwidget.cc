#define GL_SILENCE_DEPRECATION

#include "glwidget.h"

#include <QDebug>
/* #include <QFile> */

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
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/v_shader"))
    qDebug() << "Vertex shader errors:\n" << program_->log();

  if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/f_shader"))
    qDebug() << "Fragment shader errors:\n" << program_->log();


  if (!program_->link())
    qDebug() << "Shader linker errors:\n" << program_->log();

  GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                        0.0f,  0.0f,  0.5f, 0.0f};

  VBO_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  VBO_.create();
  VBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  VBO_.bind();
  VBO_.allocate(vertices, sizeof(vertices));

  VAO_.create();
  VAO_.bind();

  program_->enableAttributeArray(0);
  program_->setAttributeBuffer(0, GL_FLOAT, 0, 3);

  /* VBO_.release(); */
  /* VAO_.release(); */

  /* unsigned int indices[] = {0, 1, 3, 1, 2, 3}; */
  /* unsigned int EBO; */
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

  glDrawArrays(GL_TRIANGLES, 0, 3);
  VAO_.release();

  program_->release();
}
}  // namespace s21

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
  makeCurrent();
  VAO_.destroy();
  VBO_.destroy();
  EBO_.destroy();
  program_->disableAttributeArray(0);
  program_->release();
  delete program_;
}

void GLWidget::initializeGL() {
  // Set up the rendering context, load shaders and other resources, etc.:
  program_ = new QOpenGLShaderProgram();
  if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/v_shader"))
    qDebug() << "Vertex shader errors:\n" << program_->log();

  if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/f_shader"))
    qDebug() << "Fragment shader errors:\n" << program_->log();

  if (!program_->link())
    qDebug() << "Shader linker errors:\n" << program_->log();

  std::vector<GLfloat> vertices1{
      0.5f,  0.5f,  0.0f,  // Верхний правый угол
      0.5f,  -0.5f, 0.0f,  // Нижний правый угол
      -0.5f, -0.5f, 0.0f,  // Нижний левый угол
      -0.5f, 0.5f,  0.0f   // Верхний левый угол
  };

  std::vector<GLfloat> vertices2{
      0.0, 0.0, 0.0,  //
      0.0, 0.0, 0.5,  //
      0.0, 0.5, 0.0,  //
      0.0, 0.5, 0.5,  //
      0.5, 0.0, 0.0,  //
      0.5, 0.0, 0.5,  //
      0.5, 0.5, 0.0,  //
      0.5, 0.5, 0.5   //
  };

  std::vector<GLuint> indices1{0, 1, 3};
  std::vector<GLuint> indices2{
      0, 6, 4,  //
      0, 2, 6,  //
      0, 3, 2,  //
      0, 1, 3,  //
      2, 7, 6,  //
      2, 3, 7,  //
      4, 6, 7,  //
      4, 7, 5,  //
      0, 4, 5,  //
      0, 5, 1,  //
      1, 5, 7,  //
      1, 7, 3,  //
  };



  VAO_.create();
  VAO_.bind();

  VBO_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  VBO_.create();
  VBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  VBO_.bind();
  VBO_.allocate(vertices1.data(), vertices1.size() * sizeof(GLfloat));

  EBO_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  EBO_.create();
  EBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  EBO_.bind();
  EBO_.allocate(indices1.data(), indices1.size() * sizeof(GLuint));

  program_->enableAttributeArray(0);
  program_->setAttributeBuffer(0, GL_FLOAT, 0, 3);

  VBO_.release();
  VAO_.release();

  VAO2_.create();
  VAO2_.bind();

  VBO2_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  VBO2_.create();
  VBO2_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  VBO2_.bind();
  VBO2_.allocate(vertices2.data(), vertices2.size() * sizeof(GLfloat));

  EBO_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  EBO_.create();
  EBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  EBO_.bind();
  EBO_.allocate(indices2.data(), indices2.size() * sizeof(GLuint));

  program_->enableAttributeArray(0);
  program_->setAttributeBuffer(0, GL_FLOAT, 0, 3);

  VBO2_.release();
  VAO2_.release();

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
  /* glMatrixMode(GL_PROJECTION); */

  const QVector4D color{1.0f, 1.0f, 0.2f, 1.0f};
  program_->setUniformValue("ourColor", color);

  GLfloat x_move{0.0f}, y_move{0.0f}, z_move{-2.0f};
  QVector3D translate_vector{x_move, y_move, z_move};
  program_->setUniformValue("translateVector", translate_vector);

  GLfloat x_rotate{0.5f}, y_rotate{0.0f}, z_rotate{0.0f};
  QVector3D rotate_vector{x_rotate, y_rotate, z_rotate};
  program_->setUniformValue("rotateVector", rotate_vector);

  QMatrix4x4 perspective_matrix{};
  perspective_matrix.perspective(90.0, 1.0, 0.1, 10.0);
  /* perspective_matrix.translate(0, 0, -2.0); */
  program_->setUniformValue("perspectiveMatrix", perspective_matrix);

  program_->bind();
  /* VAO_.bind(); */
  /* glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); */
  /* VAO_.release(); */

  VAO2_.bind();
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  VAO2_.release();
}
}  // namespace s21

#define GL_SILENCE_DEPRECATION

#include "glwidget.h"

#include <QDebug>
/* #include <QFile> */
#include <vector>

namespace s21 {
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

GLWidget::GLWidget() {
  /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); */
  setMinimumWidth(660);
}

GLWidget::~GLWidget() {
  makeCurrent();
  // VAO_.destroy();
  // VBO_.destroy();
  // EBO_.destroy();
  program_->disableAttributeArray(0);
  program_->release();
  delete program_;
}

void GLWidget::Render(QOpenGLShaderProgram *program,
                      QOpenGLVertexArrayObject *VAO) {
  program_ = program;
  // (void)VAO;
  VAO->bind();
  paintGL();
  VAO->release(); 
}

void GLWidget::initializeGL() {
  GLuint vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertex_shader);
  
  GLint success;
  GLchar info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    std::cout << "VERTEX:ERROR\n" << info_log << std::endl;
  }
  
  GLuint fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    std::cout << "SHADER:ERROR\n" << info_log << std::endl;
  }

  
  shader_program_ = glCreateProgram();

  glAttachShader(shader_program_, vertex_shader);
  glAttachShader(shader_program_, fragment_shader);
  glLinkProgram(shader_program_);

  glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program_, 512, NULL, info_log);
    std::cout << "PROGRAM:ERROR\n" << info_log << std::endl;
  }

  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f, 0.5f, 0.0f
  };
  
  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);

  glBindVertexArray(VAO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  
  glUseProgram(shader_program_);

  glBindVertexArray(0);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  // Set up the rendering context, load shaders and other resources, etc.:
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
  /*     0.0, 0.0, 0.0,  // */
  /*     0.0, 0.0, 0.5,  // */
  /*     0.0, 0.5, 0.0,  // */
  /*     0.0, 0.5, 0.5,  // */
  /*     0.5, 0.0, 0.0,  // */
  /*     0.5, 0.0, 0.5,  // */
  /*     0.5, 0.5, 0.0,  // */
  /*     0.5, 0.5, 0.5   // */
  /* }; */

  /* std::vector<GLuint> indices1{0, 1, 3}; */
  /* std::vector<GLuint> indices2{ */
  /*     0, 6, 4,  // */
  /*     0, 2, 6,  // */
  /*     0, 3, 2,  // */
  /*     0, 1, 3,  // */
  /*     2, 7, 6,  // */
  /*     2, 3, 7,  // */
  /*     4, 6, 7,  // */
  /*     4, 7, 5,  // */
  /*     0, 4, 5,  // */
  /*     0, 5, 1,  // */
  /*     1, 5, 7,  // */
  /*     1, 7, 3,  // */
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
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  /* const qreal retinaScale = devicePixelRatio(); */
  /* glViewport(0, 0, width() * retinaScale, height() * retinaScale); */
  // Draw the scene:
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(shader_program_);
  glBindVertexArray(VAO_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
  /* glMatrixMode(GL_PROJECTION); */

  /* const QVector4D color{1.0f, 1.0f, 0.2f, 1.0f}; */
  /* program_->setUniformValue("ourColor", color); */

  /* GLfloat x_move{-0.25f}, y_move{-0.25f}, z_move{0.0f}; */
  /* QVector3D translate_vector{x_move, y_move, z_move}; */
  /* program_->setUniformValue("translateVector", translate_vector); */

  /* GLfloat x_rotate{0.0f}, y_rotate{0.0f}, z_rotate{0.0f}; */
  /* QVector3D rotate_vector{x_rotate, y_rotate, z_rotate}; */
  /* program_->setUniformValue("rotateVector", rotate_vector); */

  /* QMatrix4x4 perspective_matrix{}; */
  /* perspective_matrix.perspective(30.0, 1.0, 0.1, 90.0); */
  /* perspective_matrix.translate(-0.0, -0.0, -2.0); */
  /* program_->setUniformValue("perspectiveMatrix", perspective_matrix); */

  /* program_->bind(); */
  /* VAO_.bind(); */
  /* glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); */
  /* VAO_.release(); */

  /* VAO2_.bind(); */
  /* glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); */
  /* VAO2_.release(); */
}
}  // namespace s21

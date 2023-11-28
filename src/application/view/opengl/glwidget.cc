#define GL_SILENCE_DEPRECATION

#include "glwidget.h"

#include "shaderreader.h"

#include <QFile>
#include <QDebug>

namespace s21 {
GLWidget::GLWidget() {
  /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); */
  setMinimumWidth(660);
}

void GLWidget::initializeGL() {
  // Set up the rendering context, load shaders and other resources, etc.:
  initializeOpenGLFunctions();

  /* std::string vertexShaderStringSource = */
  /*     ReadShader("./application/view/opengl/v_shader.glsl"); */
  /* const char *vertexShaderSource = vertexShaderStringSource.c_str(); */
  /* std::string fragmentShaderStringSource = */
  /*     ReadShader("./application/view/opengl/f_shader.glsl"); */
  /* const char *fragmentShaderSource = fragmentShaderStringSource.c_str(); */

/*   const char *vertexShaderSource = */
/*       "#version 410 core\n" */
/*       "in vec3 vertexPosition_modelspace;" */
/*       "void main() {" */
/*       "    gl_Position.xyz = vertexPosition_modelspace;" */
/*       "    gl_Position.w = 1.0;" */
/*       "}"; */
  /* program.addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/joramuns/Projects/CPP4_3DViewer_v2.0-2/src/application/view/opengl/v_shader.glsl"); */

  /* const char *fragmentShaderSource = */
  /*     "#version 410 core\n" */
  /*     "out vec3 color;" */
  /*     "void main() {" */
  /*     "    color = vec3(1.0, 0.0, 0.0);" */
  /*     "}"; */
  /* program.addShaderFromSourceFile(QOpenGLShader::Fragment, */
  /*                                 fragmentShaderSource); */

  /* program.link(); */

  GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                        0.0f,  0.0f,  0.5f, 0.0f};

  /* unsigned int vertexShader = f->glCreateShader(GL_VERTEX_SHADER); */
  /* f->glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); */
  /* f->glCompileShader(vertexShader); */

  /* unsigned int fragmentShader = f->glCreateShader(GL_FRAGMENT_SHADER); */
  /* f->glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); */
  /* f->glCompileShader(fragmentShader); */

  /* unsigned int shaderProgram = f->glCreateProgram(); */
  /* f->glAttachShader(shaderProgram, vertexShader); */
  /* f->glAttachShader(shaderProgram, fragmentShader); */
  /* f->glLinkProgram(shaderProgram); */
  /* f->glUseProgram(shaderProgram); */

  /* f->glDeleteShader(vertexShader); */
  /* f->glDeleteShader(fragmentShader); */

  /* unsigned int indices[] = {0, 1, 3, 1, 2, 3}; */

  /* unsigned int VBO, EBO; */

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // 0. copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  /* f->glGenBuffers(1, &EBO); */
  /* f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); */
  /* f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
   * GL_STATIC_DRAW); */

  /* /1* f->glGenVertexArrays(1, &VAO); *1/ */
  /* /1* f->glBindVertexArray(VAO); *1/ */
  /* // 1. then set the vertex attributes pointers */
  /* f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
   * *)0); */
  /* f->glEnableVertexAttribArray(0); */

  /* // 2. use our shader program when we want to render an object */
  /* f->glUseProgram(shaderProgram); */
  /* // 3. now draw the object */
  /* f->glDrawArrays(GL_TRIANGLES, 0, 3); */
}

void GLWidget::resizeGL(int w, int h) {
  // Update projection matrix and other size related settings:
  (void)w;
  (void)h;
  /* m_projection.setToIdentity(); */
  /* m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f); */
}

void GLWidget::paintGL() {
  // Draw the scene:
  glClear(GL_COLOR_BUFFER_BIT);
  /* program.bind(); */

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
  /* program.release(); */
  /* QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions(); */
  /* f->glClear(GL_COLOR_BUFFER_BIT); */
}
}  // namespace s21

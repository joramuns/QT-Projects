#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#include "glwidget.h"
#include "stb_image.h"

#include <QDebug>
/* #include <QFile> */
#include <iostream>
#include <vector>

namespace s21 {
GLWidget::GLWidget() {
  /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); */
  setMinimumWidth(660);
}

GLWidget::~GLWidget() {
  makeCurrent();
  for (auto &item : GLBuffers_)
    delete item;
  program_->disableAttributeArray(0);
  program_->release();
  delete program_;
}

void GLWidget::LoadModel(std::vector<GLfloat> vertices) {
  GLBuffers_.emplace_back(new GLBuffer(vertices, program_));
  update();
}

void GLWidget::UnloadModel(int model_number) {
  GLBuffers_.erase(GLBuffers_.begin() + model_number);
  update();
}

void GLWidget::Rotate(double value, char axis, int model_number) {
  GLBuffers_[model_number]->Rotate(value, axis);
}

void GLWidget::Move(double value, char axis, int model_number) {
  GLBuffers_[model_number]->Move(value, axis);
}

void GLWidget::Scale(double value, int model_number) {
  GLBuffers_[model_number]->Scale(value);
}

void GLWidget::initializeGL() {
  // Set up the rendering context, load shaders and other resources, etc.:
  LoadShaders();
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
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
  glClearColor(0.2, 0.1, 0.1, 1.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDepthFunc(GL_LESS);
  program_->bind();
  
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  
  int width, height, channels;
  unsigned char *image =
      stbi_load("/Users/mammiemi/Project/CPP4_3DViewer_v2.0-2/src/application/"
                "view/opengl/mramor.jpeg",
                &width, &height, &channels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  for (std::size_t i = 0; i < GLBuffers_.size(); ++i) {
    GLBuffers_[i]->Bind();
    GLBuffers_[i]->LoadUniforms();
    LoadCommonUniforms();

    glDrawArrays(GL_TRIANGLES, 0, GLBuffers_[i]->GetBuffSize());
    GLBuffers_[i]->Release();
    // GLBuffers_[i]->BindNormals();
    // GLBuffers_[i]->ReleaseNormals();
  }
  // glEnable(GL_DEPTH_TEST);
  program_->release();
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

void GLWidget::LoadCommonUniforms() {

  QMatrix4x4 perspective_matrix{};
  perspective_matrix.perspective(30.0, 1.0, 0.1, 90.0);
  perspective_matrix.translate(-0.0, -0.0, -2.0);
  program_->setUniformValue("perspectiveMatrix", perspective_matrix);
}

} // namespace s21

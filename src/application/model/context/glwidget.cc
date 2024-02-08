#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#include "glwidget.h"

#include <QDebug>
#include <iostream>
#include <vector>

namespace s21 {
GLWidget::GLWidget()
    : bg_color_(100, 100, 100, 1),
      vert_color_(0.95, 0.95, 0.95),
      edge_color_(0.95, 0.15, 0.85),
      central_projection_(false),
      solid_(false),
      vert_type_(2),
      vert_size_(10.0),
      dashed_lines_(false) {
  /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); */
  setMinimumWidth(660);
}

GLWidget::~GLWidget() {
  makeCurrent();
  for (auto &item : GLBuffers_) delete item;
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

void GLWidget::SwitchProjection(int index) { central_projection_ = index; }

void GLWidget::SwitchWireframe(int index) { solid_ = index; }

void GLWidget::SetSceneColor(QColor color) { bg_color_ = color; }

void GLWidget::SetVertexColor(QVector3D color) { vert_color_ = color; }

void GLWidget::SetEdgeColor(QVector3D color) { edge_color_ = color; }

void GLWidget::SetVertexOption(int index) { vert_type_ = index; }

void GLWidget::SetEdgeOption(int index) {
  dashed_lines_ = static_cast<bool>(index);
}

void GLWidget::SetEdgeSize(double value) {
  edge_size_ = static_cast<GLfloat>(value);
}

void GLWidget::SetVertexSize(double value) {
  std::cout << "glwidget size vert " << value << " " << vert_size_ << std::endl;
  vert_size_ = static_cast<GLfloat>(value);
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
  float lineWidth[2];
  glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, lineWidth);
  std::cout << "WIDTH TEST: " << lineWidth[0] << " " << lineWidth[1]
            << std::endl;
  if (solid_) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  } else {
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(edge_size_);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  /* const qreal retinaScale = devicePixelRatio(); */
  /* glViewport(0, 0, width() * retinaScale, height() * retinaScale); */
  // Draw the scene:
  glClearColor(bg_color_.redF(), bg_color_.greenF(), bg_color_.blueF(),
               bg_color_.alphaF());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDepthFunc(GL_LESS);
  program_->bind();
  std::cout << "glwidget edge size: " << edge_size_ << std::endl;

  for (std::size_t i = 0; i < GLBuffers_.size(); ++i) {
    GLBuffers_[i]->Bind();
    GLBuffers_[i]->LoadUniforms();
    LoadCommonUniforms();

    glDrawArrays(GL_TRIANGLES, 0, GLBuffers_[i]->GetBuffSize());
    if (vert_type_) {
      program_->setUniformValue("vertexType", vert_type_);
      program_->setUniformValue("modelColor", vert_color_);
      glPointSize(vert_size_);
      glDrawArrays(GL_POINTS, 0, GLBuffers_[i]->GetBuffSize());
      program_->setUniformValue("vertexType", 0);
    }
    GLBuffers_[i]->Release();
  }
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
  if (central_projection_) {
    perspective_matrix.perspective(30.0, 1.0, 0.1, 90.0);
    perspective_matrix.translate(-0.0, -0.0, -2.0);
  }
  program_->setUniformValue("perspectiveMatrix", perspective_matrix);
  program_->setUniformValue("modelColor", edge_color_);
  program_->setUniformValue("dashedLines", dashed_lines_);
  program_->setUniformValue("resolution", width(), height());
}

}  // namespace s21

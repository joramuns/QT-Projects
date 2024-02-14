#include "glwidget.h"

namespace s21 {
GLWidget::GLWidget() : settings_(SettingsSingleton::GetInstance()) {
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
  delete GLBuffers_[model_number];
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

void GLWidget::SaveScreenshot(const QString &filename) {
  QImage screenshot = grabFramebuffer();
  screenshot.save(filename);
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
  SceneLoader();
  ModelLoader();
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

void GLWidget::SceneLoader() {
  if (settings_.GetPolygonType()) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  } else {
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(settings_.GetEdgeSize());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  const QColor bg_color = settings_.GetBGColor();
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(),
               bg_color.alphaF());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDepthFunc(GL_LESS);
}

void GLWidget::ModelLoader() {
  program_->bind();
  for (std::size_t i = 0; i < GLBuffers_.size(); ++i) {
    GLBuffers_[i]->Bind();
    GLBuffers_[i]->LoadUniforms();
    LoadCommonUniforms();

    glDrawArrays(GL_TRIANGLES, 0, GLBuffers_[i]->GetBuffSize());
    if (settings_.GetVertexType()) {
      program_->setUniformValue("vertexType", settings_.GetVertexType());
      program_->setUniformValue("modelColor", settings_.GetVertexColor());
      glPointSize(settings_.GetVertexSize());
      glDrawArrays(GL_POINTS, 0, GLBuffers_[i]->GetBuffSize());
      program_->setUniformValue("vertexType", 0);
    }
    GLBuffers_[i]->Release();
  }
  program_->release();
}

void GLWidget::LoadCommonUniforms() {
  QMatrix4x4 perspective_matrix{};
  if (settings_.GetProjectionType()) {
    perspective_matrix.perspective(30.0, 1.0, 0.1, 90.0);
    perspective_matrix.translate(-0.0, -0.0, -2.0);
  }
  program_->setUniformValue("perspectiveMatrix", perspective_matrix);
  program_->setUniformValue("modelColor", settings_.GetEdgeColor());
  program_->setUniformValue("dashedLines", settings_.GetEdgeType());
  program_->setUniformValue("resolution", width(), height());
}

}  // namespace s21

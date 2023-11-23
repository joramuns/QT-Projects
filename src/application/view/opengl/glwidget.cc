#include "glwidget.h"

namespace s21 {
  GLWidget::GLWidget() {
    /* setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); */
    setMinimumWidth(660);
  }

  void GLWidget::initializeGL() {
    // Set up the rendering context, load shaders and other resources, etc.:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
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
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
  }
}

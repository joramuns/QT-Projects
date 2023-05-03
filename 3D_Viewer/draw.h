#ifndef DRAW_H
#define DRAW_H

// #include <QImageWriter>
// #include <QOpenGLFramebufferObject>
// #include <QPainter>
// #include <QTimer>
// #include <QMovie>
// #include <QThread>

#include <QFileDialog>
#include <math.h>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
// #include <QTimer>
#include <QColorDialog>

#if defined(__APPLE__)
#include <OpenGL/glu.h>
#elif defined(__unix__)
#include <GL/glu.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include "c-function/core/core.h"
#include "c-function/core/pars.h"
#ifdef __cplusplus
}
#endif

enum PrefMask {
  kProjection = 1,
  kChangeProjection,
  kDashed,
  kVertex,
  kSquareVertex,
};

struct Prefs {
  QColor bg_color;
  QColor vertex_color;
  QColor faces_color;
  unsigned bit_bools;
  GLdouble v_size;
  GLdouble l_size;
};

class Draw : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT;

public:
  explicit Draw(QWidget *parent = nullptr);

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  Pars_counters view = {0, 0, 0, 0, 0, 0};
  GLuint VBO = 0;
  Prefs preferences = {
      .bg_color = QColor(0, 0, 0),
      .vertex_color = QColor(255, 255, 255),
      .faces_color = QColor(0, 255, 0),
      .bit_bools = 0,
      .v_size = 3,
      .l_size = 1,
  };

  void disabler();

public Q_SLOTS:

  void setPref(PrefMask mask, bool setter);
  bool getPref(PrefMask mask);
  void cleanView();
  void changeProjection();
};

#endif // DRAW_H

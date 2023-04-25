#ifndef DRAW_H
#define DRAW_H

#include <QGridLayout>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QFileDialog>
#include <QColorDialog>

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
  kDashed,
  kVertex,
  kSquareVertex
};

struct Prefs {
  QColor bg_color;
  QColor vertex_color;
  QColor faces_color;
  unsigned bit_bools;
  GLuint v_size;
  GLuint l_size;
};

class Draw : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT;

public:
  explicit Draw(QWidget *parent = nullptr);

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  Pars_counters view = {0, 0, 0, 0, 0, 0};
  QString fileName;
  const char *file_name;
  // char *filename = "/Users/mammiemi/Desktop/C8_3DViewer_v1.0-2/src/3D_Viewer/"
  //                  "c-function/core/coub.obj";

public Q_SLOTS:
  void left_move();
  void right_move();
  void up_move();
  void down_move();

  void turn_x();
  void turn_counter_x();

  void turn_y();
  void turn_counter_y();

  void turn_z();
  void turn_counter_z();

  void scale_plus();
  void scale_minus();

  void select_file();
  void bg_select_color();
  void vertex_select_color();
  void faces_select_color();

  void toggle_pref(PrefMask mask);
  void setVertexSize(int size);
  void setLineSize(int size);

private:
  Prefs preferences = {
    .bg_color = QColor(0, 0, 0),
    .vertex_color = QColor(255, 255, 255),
    .faces_color = QColor(0, 255, 0),
    .bit_bools = 0,
    .v_size = 1,
    .l_size = 1,
  };
  void setPref(Prefs& source, PrefMask mask, bool setter);
  bool getPref(const Prefs& source, PrefMask mask);
};

#endif // DRAW_H

#ifndef DRAW_H
#define DRAW_H

#include <QGridLayout>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QFileDialog>

#ifdef __cplusplus
extern "C" {
#endif
#include "c-function/core/core.h"
#include "c-function/core/pars.h"
#ifdef __cplusplus
}
#endif

class Draw : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT;

public:
  explicit Draw(QWidget *parent = nullptr);

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  Pars_counters view;
  QString fileName;
  const char *file_name;
  int perspective=1;

public Q_SLOTS:
  void left_move();
  void right_move();
  void up_move();
  void down_move();
  void in_move();
  void out_move();

  void turn_x();
  void turn_counter_x();

  void turn_y();
  void turn_counter_y();

  void turn_z();
  void turn_counter_z();

  void scale_plus();
  void scale_minus();

  void select_file();

  void perspective_change();
};

#endif // DRAW_H

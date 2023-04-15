#ifndef PAINT_H
#define PAINT_H

#include <QGridLayout>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>

#ifdef __cplusplus
extern "C" {
#endif
    #include "c-function/core/core.h"
#ifdef __cplusplus
}
#endif

class Paint : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT;

public:
  explicit Paint(QWidget *parent = nullptr);
  
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  float *point_array;

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
};

#endif // PAINT_H

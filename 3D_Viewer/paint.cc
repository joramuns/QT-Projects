#include "paint.h"
#if defined(__APPLE__)
#include <OpenGL/glu.h>
#elif defined(__unix__)
#include <GL/glu.h>
#endif
#include <math.h>

#define SHIFT 0.03

Paint::Paint(QWidget *parent) : QOpenGLWidget(parent) {}

void Paint::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  point_array = sort_array(point_array);
  this->resize(800, 800);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Paint::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(-1, 1, -1, 1, -1, 2);
  gluPerspective(60, 1, 0.5, 100);
}

void Paint::paintGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -2);
  glColor3f(1.0f, 0.0f, 0.0f);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT),
                        point_array);
  glDrawArrays(GL_TRIANGLES, 0, 4);
  glDisableVertexAttribArray(0);
  /* glEnd(); */
}

void Paint::left_move() {
  coordinate_change(-SHIFT, 0.0, 0.0, point_array);
  repaint();
}

void Paint::right_move() {
  coordinate_change(SHIFT, 0.0, 0.0, point_array);
  repaint();
}

void Paint::up_move() {
  coordinate_change(0.0, SHIFT, 0.0, point_array);
  repaint();
}

void Paint::down_move() {
  coordinate_change(0.0, -SHIFT, 0.0, point_array);
  repaint();
}

void Paint::turn_x() {
  turn_matrix_x(SHIFT, point_array);
  repaint();
}

void Paint::turn_counter_x() {
  turn_matrix_x(-SHIFT, point_array);
  repaint();
}

void Paint::turn_y() {
  turn_matrix_y(SHIFT, point_array);
  repaint();
}

void Paint::turn_counter_y() {
  turn_matrix_y(-SHIFT, point_array);
  repaint();
}

void Paint::turn_z() {
  turn_matrix_z(SHIFT, point_array);
  repaint();
}

void Paint::turn_counter_z() {
  turn_matrix_z(-SHIFT, point_array);
  repaint();
}

void Paint::scale_plus() {
  scaling(1 + SHIFT, point_array);
  repaint();
}

void Paint::scale_minus() {
  scaling(1 - SHIFT, point_array);
  repaint();
}

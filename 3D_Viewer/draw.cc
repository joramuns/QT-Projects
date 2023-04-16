#include "draw.h"
#if defined(__APPLE__)
#include <OpenGL/glu.h>
#elif defined(__unix__)
#include <GL/glu.h>
#endif
#include <math.h>

#define SHIFT 0.03

Draw::Draw(QWidget *parent) : QOpenGLWidget(parent) {}

void Draw::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  array_sort(point_array,
             "/Users/mammiemi/Desktop/C8_3DViewer_v1.0-2/src/3D_Viewer/"
             "c-function/core/coub.obj",
             &count_vertex, &cound_side);
  this->resize(800, 800);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Draw::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(-1, 1, -1, 1, -1, 2);
  gluPerspective(60, 1, 0.5, 100);
}

void Draw::paintGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -2);
  glColor3f(1.0f, 0.0f, 0.0f);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT),
                        point_array);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(GL_TRIANGLES, 0, 4);
  glDisableVertexAttribArray(0);
  /* glEnd(); */
}

void Draw::left_move() {
  coordinate_change(-SHIFT, 0.0, 0.0, point_array);
  repaint();
}

void Draw::right_move() {
  coordinate_change(SHIFT, 0.0, 0.0, point_array);
  repaint();
}

void Draw::up_move() {
  coordinate_change(0.0, SHIFT, 0.0, point_array);
  repaint();
}

void Draw::down_move() {
  coordinate_change(0.0, -SHIFT, 0.0, point_array);
  repaint();
}

void Draw::turn_x() {
  turn_matrix_x(SHIFT, point_array);
  repaint();
}

void Draw::turn_counter_x() {
  turn_matrix_x(-SHIFT, point_array);
  repaint();
}

void Draw::turn_y() {
  turn_matrix_y(SHIFT, point_array);
  repaint();
}

void Draw::turn_counter_y() {
  turn_matrix_y(-SHIFT, point_array);
  repaint();
}

void Draw::turn_z() {
  turn_matrix_z(SHIFT, point_array);
  repaint();
}

void Draw::turn_counter_z() {
  turn_matrix_z(-SHIFT, point_array);
  repaint();
}

void Draw::scale_plus() {
  scaling(1 + SHIFT, point_array);
  repaint();
}

void Draw::scale_minus() {
  scaling(1 - SHIFT, point_array);
  repaint();
}

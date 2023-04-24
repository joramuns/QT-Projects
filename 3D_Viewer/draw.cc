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
  view = {0, 0, 0, 0, 0, 0};
  FILE *obj = fopen(filename, "r");
  if (obj == NULL) {
    // its warning time;
  } else {
    array_sort(obj, &view);
    fclose(obj);
  }
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
  glColor3f(0.0f, 1.0f, 0.0f);
  GLuint buffer_id;
  glGenBuffers(1, &buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, view.size_sort_array * sizeof(GL_FLOAT),
               view.sorted_array, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glLineStipple(1, 3);
  glEnable(GL_LINE_STIPPLE);
  glDrawArrays(GL_TRIANGLES, 0, view.size_sort_array);
  glDisable(GL_LINE_STIPPLE);

  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glPointSize(10.0f);

  glDrawArrays(GL_POINTS, 0, view.size_sort_array);

  glDisable(GL_POINT_SMOOTH);
  glDisableVertexAttribArray(0);
  glDeleteBuffers(1, &buffer_id);
}

void Draw::left_move() {
  coordinate_change(-SHIFT, 0.0, 0.0, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::right_move() {
  coordinate_change(SHIFT, 0.0, 0.0, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::up_move() {
  coordinate_change(0.0, SHIFT, 0.0, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::down_move() {
  coordinate_change(0.0, -SHIFT, 0.0, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::turn_x() {
  turn_matrix_x(SHIFT, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::turn_counter_x() {
  turn_matrix_x(-SHIFT, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::turn_y() {
  turn_matrix_y(SHIFT, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::turn_counter_y() {
  turn_matrix_y(-SHIFT, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::turn_z() {
  turn_matrix_z(SHIFT, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::turn_counter_z() {
  turn_matrix_z(-SHIFT, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::scale_plus() {
  scaling(1 + SHIFT, view.sorted_array, view.size_sort_array);
  repaint();
}

void Draw::scale_minus() {
  scaling(1 - SHIFT, view.sorted_array, view.size_sort_array);
  repaint();
}

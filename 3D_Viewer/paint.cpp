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

QVector<float> Paint::turn_matrix_x(float theta, QVector<float> point) {
  QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

  matrix_scale[0][0] = 1.0;
  matrix_scale[0][1] = 0.0;
  matrix_scale[0][2] = 0.0;
  matrix_scale[0][3] = 0.0;

  matrix_scale[1][0] = 0.0;
  matrix_scale[1][1] = cos(theta);
  matrix_scale[1][2] = -sin(theta);
  matrix_scale[1][3] = 0.0;

  matrix_scale[2][0] = 0.0;
  matrix_scale[2][1] = sin(theta);
  matrix_scale[2][2] = cos(theta);
  matrix_scale[2][3] = 0.0;

  matrix_scale[3][0] = 0.0;
  matrix_scale[3][1] = 0.0;
  matrix_scale[3][2] = 0.0;
  matrix_scale[3][3] = 1.0;

  QVector<float> result(4);
  for (int i = 0; i < 4; i++) {
    float sum = 0.0f;
    for (int j = 0; j < 4; j++) {
      sum += matrix_scale[i][j] * point[j];
    }
    result[i] = sum;
  }
  return result;
}

void Paint::curent_turn_x(float theta) {}

void Paint::turn_x() {
  curent_turn_x(SHIFT);
  repaint();
}

void Paint::turn_counter_x() {
  curent_turn_x(-SHIFT);
  repaint();
}

QVector<float> Paint::turn_matrix_y(float theta, QVector<float> point) {
  QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

  matrix_scale[0][0] = cos(theta);
  matrix_scale[0][1] = 0.0;
  matrix_scale[0][2] = sin(theta);
  matrix_scale[0][3] = 0.0;

  matrix_scale[1][0] = 0.0;
  matrix_scale[1][1] = 1.0;
  matrix_scale[1][2] = 0.0;
  matrix_scale[1][3] = 0.0;

  matrix_scale[2][0] = -sin(theta);
  matrix_scale[2][1] = 0.0;
  matrix_scale[2][2] = cos(theta);
  matrix_scale[2][3] = 0.0;

  matrix_scale[3][0] = 0.0;
  matrix_scale[3][1] = 0.0;
  matrix_scale[3][2] = 0.0;
  matrix_scale[3][3] = 1.0;

  QVector<float> result(4);
  for (int i = 0; i < 4; i++) {
    float sum = 0.0f;
    for (int j = 0; j < 4; j++) {
      sum += matrix_scale[i][j] * point[j];
    }
    result[i] = sum;
  }
  return result;
}

void Paint::curent_turn_y(float theta) {}

void Paint::turn_y() {
  curent_turn_y(SHIFT);
  repaint();
}

void Paint::turn_counter_y() {
  curent_turn_y(-SHIFT);
  repaint();
}

QVector<float> Paint::turn_matrix_z(float theta, QVector<float> point) {
  QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

  matrix_scale[0][0] = cos(theta);
  matrix_scale[0][1] = -sin(theta);
  matrix_scale[0][2] = 0.0;
  matrix_scale[0][3] = 0.0;

  matrix_scale[1][0] = sin(theta);
  matrix_scale[1][1] = cos(theta);
  matrix_scale[1][2] = 0.0;
  matrix_scale[1][3] = 0.0;

  matrix_scale[2][0] = 0.0;
  matrix_scale[2][1] = 0.0;
  matrix_scale[2][2] = 1.0;
  matrix_scale[2][3] = 0.0;

  matrix_scale[3][0] = 0.0;
  matrix_scale[3][1] = 0.0;
  matrix_scale[3][2] = 0.0;
  matrix_scale[3][3] = 1.0;

  QVector<float> result(4);
  for (int i = 0; i < 4; i++) {
    float sum = 0.0f;
    for (int j = 0; j < 4; j++) {
      sum += matrix_scale[i][j] * point[j];
    }
    result[i] = sum;
  }
  return result;
}

void Paint::curent_turn_z(float theta) {}

void Paint::turn_z() {
  curent_turn_z(SHIFT);
  repaint();
}

void Paint::turn_counter_z() {
  curent_turn_z(-SHIFT);
  repaint();
}

QVector<float> Paint::scaling(float x, QVector<float> point) {
  QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

  matrix_scale[0][0] = x;
  matrix_scale[0][1] = 0.0;
  matrix_scale[0][2] = 0.0;
  matrix_scale[0][3] = 0.0;

  matrix_scale[1][0] = 0.0;
  matrix_scale[1][1] = x;
  matrix_scale[1][2] = 0.0;
  matrix_scale[1][3] = 0.0;

  matrix_scale[2][0] = 0.0;
  matrix_scale[2][1] = 0.0;
  matrix_scale[2][2] = x;
  matrix_scale[2][3] = 0.0;

  matrix_scale[3][0] = 0.0;
  matrix_scale[3][1] = 0.0;
  matrix_scale[3][2] = 0.0;
  matrix_scale[3][3] = 1.0;

  QVector<float> result(4);
  for (int i = 0; i < 4; i++) {
    float sum = 0.0f;
    for (int j = 0; j < 4; j++) {
      sum += matrix_scale[i][j] * point[j];
    }
    result[i] = sum;
  }
  return result;
}

void Paint::scale_plus() { repaint(); }

void Paint::scale_minus() { repaint(); }

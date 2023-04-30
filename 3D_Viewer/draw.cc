#define GL_SILENCE_DEPRECATION
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
  cleanView();
  changeProjection();
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Draw::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void Draw::paintGL() {
  if (!VBO) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, view.size_sort_array * sizeof(GL_FLOAT),
                 view.sorted_array, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (getPref(kChangeProjection)) {
    changeProjection();
  }
  glBufferSubData(GL_ARRAY_BUFFER, 0, view.size_sort_array * sizeof(GL_FLOAT), view.sorted_array);
  glClearColor(
      preferences.bg_color.redF(), 
      preferences.bg_color.greenF(), 
      preferences.bg_color.blueF(), 
      preferences.bg_color.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(
      preferences.faces_color.redF(),
      preferences.faces_color.greenF(),
      preferences.faces_color.blueF());

  glLineWidth(preferences.l_size);
  if (getPref(kDashed)) {
    glLineStipple(1, 3);
    glEnable(GL_LINE_STIPPLE);
    glDrawArrays(GL_TRIANGLES, 0, view.size_sort_array);
    glDisable(GL_LINE_STIPPLE);
  } else {
    glDrawArrays(GL_TRIANGLES, 0, view.size_sort_array);
  }

  if (getPref(kVertex)) {
    bool squared = getPref(kSquareVertex); 
    if (!squared) {
      glEnable(GL_POINT_SMOOTH);
      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    }
    glPointSize(preferences.v_size);
    glColor3f(
        preferences.vertex_color.redF(),
        preferences.vertex_color.greenF(),
        preferences.vertex_color.blueF());
    glDrawArrays(GL_POINTS, 0, view.size_sort_array);
    if (!squared) {
      glDisable(GL_POINT_SMOOTH);
    }
  }
}

void Draw::disabler() {
  glDisableVertexAttribArray(0);
  glDeleteBuffers(1, &VBO);
  VBO = 0;
}

void Draw::setPref(PrefMask mask, bool setter) {
  if (setter) {
    preferences.bit_bools |= 1U << mask;
  } else {
    preferences.bit_bools &= ~(1U << mask);
  }
}

bool Draw::getPref(PrefMask mask) {
  return preferences.bit_bools & (1U << mask);
}

void Draw::cleanView() {
  if (view.sorted_array) {
    free(view.sorted_array);
    view.count_vertex = 0;
    view.count_side = 0;
    view.size_sort_array = 0;
    view.size_unsort_memory = 0;
    view.size_sort_memory = 0;
    view.sorted_array = NULL;
  }
}

void Draw::changeProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (getPref(kProjection)) {
    glOrtho(-1, 1, -1, 1, 0, 10);
  } else {
    gluPerspective(60, 1, 0.5, 100);
  }
  glTranslatef(0, 0, -2);
  setPref(kChangeProjection, false);
}

#include <GL/glut.h>

namespace s21 {

struct PointCoordinates {
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat a{0.0};
};

struct TexturesCoordinates {
  GLfloat u;
  GLfloat v;
  GLfloat w{0.0};
};

struct NormalsCoordinate {
  GLfloat x;
  GLfloat y;
  GLfloat z;
};
} // namespace s21
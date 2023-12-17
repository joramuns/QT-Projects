#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_COORDINATE_STRUCT_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_COORDINATE_STRUCT_H
// #include <GL/glut.h>
#include <OpenGL/gl.h>

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

#endif // CPP4_3DVIEWER_V2_MODEL_PARSER_COORDINATE_STRUCT_H
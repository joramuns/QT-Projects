/*!
\file
\brief Заголовочный файл с описанием структур

Данный файл содержит в себе определения структур,
которые используются для заполнения значениями координат параметров
*/
#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_COORDINATE_STRUCT_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_COORDINATE_STRUCT_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif  // __APPLE__

#ifdef __linux__
#include <GL/glut.h>
#endif  // __linux__

namespace s21 {

/// @brief Структура хранящая в себе значения координат точек полигона в
/// трехмерном пространстве
struct PointCoordinates {
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat a{0.0};
};

/// @brief Структура хранящая в себе значения координат точек текстуры для
/// полигона
struct TexturesCoordinates {
  GLfloat u;
  GLfloat v;
  // GLfloat w{0.0};
};

/// @brief Структура хранящая в себе значения координат вектора нормали полигона
struct NormalsCoordinate {
  GLfloat x;
  GLfloat y;
  GLfloat z;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_PARSER_COORDINATE_STRUCT_H

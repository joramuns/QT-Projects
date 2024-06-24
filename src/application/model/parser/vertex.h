/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса Vertex
*/
#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_VERTEX_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_VERTEX_H
#include <QVector3D>

namespace s21 {
struct Vertex {
  QVector3D position;
  QVector3D normal;
  QVector2D texCoord;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_MODEL_PARSER_VERTEX_H

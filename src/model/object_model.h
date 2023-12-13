#ifndef CPP4_3DVIEWER_V2_MODEL_OBJECT_MODEL_H
#define CPP4_3DVIEWER_V2_MODEL_OBJECT_MODEL_H
#include <OpenGL/gl.h>
#include <string>
#include <vector>

#include <iostream>

#include "parser/parser.h"

namespace s21 {
class ObjectModel {
public:
  ObjectModel() = delete;
  explicit ObjectModel(const std::string &filename);
  ~ObjectModel();

  std::vector<std::vector<GLfloat>> GetVertices() const noexcept;
  std::vector<std::vector<GLfloat>> GetTextures() const noexcept;
  std::vector<std::vector<GLfloat>> GetNormals() const noexcept;

  std::vector<std::vector<GLuint>> GetVertexIndexes() const noexcept;
  std::vector<std::vector<GLuint>> GetTextureIndexes() const noexcept;
  std::vector<std::vector<GLuint>> GetNormalIndexes() const noexcept;

  //debug
  void PrintResult() const noexcept;
private:
  /// need class Setting
  std::string filename_;
  std::vector<std::vector<GLfloat>> all_vertices_;
  std::vector<std::vector<GLfloat>> all_textures_;
  std::vector<std::vector<GLfloat>> all_normals_;

  std::vector<std::vector<GLuint>> vertex_indexes_;
  std::vector<std::vector<GLuint>> texture_indexes_;
  std::vector<std::vector<GLuint>> normal_indexes_;
};
} // namespace s21

#endif // CPP4_3DVIEWER_V2_MODEL_OBJECT_MODEL_H
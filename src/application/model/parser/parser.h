#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_PARSER_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_PARSER_H
#include <OpenGL/gl.h>
// #include <GL/glut.h>
// #include <glm/glm.hpp>
/* -I/Users/joramuns/.brew/Cellar/glm/0.9.9.8/include */
/* brew install glm */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "struct/coordinatestruct.h"
#include "indices_pars/faces_strategy.h"

#define BAD_FILENAME 1

namespace s21 {
class Parser {
public:
  Parser() = delete;
  explicit Parser(const std::string &filename);
  ~Parser();

  std::vector<std::vector<GLfloat>> GetCoordinates() const noexcept;
  // std::vector<std::vector<GLfloat>> GetTextures() const noexcept;
  // std::vector<std::vector<GLfloat>> GetNormals() const noexcept;

  std::vector<std::vector<GLuint>> GetIndexes() const noexcept;
  // std::vector<std::vector<GLuint>> GetTextureIndexes() const noexcept;
  // std::vector<std::vector<GLuint>> GetNormalIndexes() const noexcept;
private:
  int ReadObj(const std::string &filename);

  void AddPointInArray() noexcept;
  void DataClear() noexcept;
  void AddPoint(std::istringstream &data) noexcept;
  void AddTexturePoint(std::istringstream &data) noexcept;
  void AddNormalsPoint(std::istringstream &data) noexcept;
  void SetStrategy(std::ifstream *file, int current_position) noexcept;
  void StructFill(const PointCoordinates &vertices_struct) noexcept;
  void StructFill(const TexturesCoordinates &textures_struct) noexcept;
  void StructFill(const NormalsCoordinate &normals_struct) noexcept;
  void GetIndexes() noexcept;
  void Packer() noexcept;

  void DebugPrint() noexcept;

private:
  std::vector<GLfloat> vertex_points_;
  std::vector<GLfloat> texture_points_;
  std::vector<GLfloat> normal_points_;

  std::vector<std::vector<GLfloat>> all_vertices_; // may b list
  std::vector<std::vector<GLfloat>> all_textures_;
  std::vector<std::vector<GLfloat>> all_normals_;

  std::vector<std::vector<GLuint>> vertex_faces_;
  std::vector<std::vector<GLuint>> texture_faces_;
  std::vector<std::vector<GLuint>> normal_faces_;
  
  std::vector<std::vector<GLfloat>> coordinates_;
  std::vector<std::vector<GLuint>> indices_;

  FacesStrategy *faces_pars_;
};
} // namespace s21
#endif // CPP4_3DVIEWER_V2_MODEL_PARSER_PARSER_H
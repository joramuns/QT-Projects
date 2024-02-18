/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса парсера, считывающего и
сортирующего данные из файла obj формата, для работы с ними в  OpenGL
*/
#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_NEWPARSER_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_NEWPARSER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif // __APPLE__

#ifdef __linux__
#include <GL/glut.h>
#endif // __linux__

#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "struct/coordinatestruct.h"

// for debug
#include <iostream>

namespace s21 {
class NewParser {
public:
  explicit NewParser(const std::string &filename);

  ~NewParser() = default;

  std::vector<std::vector<GLfloat>> GetCoordinates() const noexcept;

private:
  bool IsCorrectFileFormat(const std::string &filename) const noexcept;
  bool IsFileExist(const std::string &filename) const noexcept;

  void DataRead(const std::string &filename) noexcept;

  bool VertexRead(std::ifstream *file, int &file_position) noexcept;
  bool IsVertexData(const std::string &data) const noexcept;
  void VertexPointFill(const std::string &data) noexcept;

  bool TexturesRead(std::ifstream *file, int &file_position) noexcept;
  bool IsTexturesData(const std::string &data) const noexcept;
  void TexturesPointFill(const std::string &data) noexcept;

  bool NormalsRead(std::ifstream *file, int &file_position) const noexcept;
  bool IsNormalsData(const std::string &data) const noexcept;
  void NormalsPointFill(const std::string &data) noexcept;

private:
  std::vector<std::vector<GLfloat>> coordinates_;

  std::vector<GLfloat> vertices_;
  std::vector<std::vector<GLfloat>> all_vertices_;
  
  std::vector<GLfloat> textures_;
  std::vector<std::vector<GLfloat>> all_textures_;

  bool vertices_is_read{false};
  bool textures_is_read{false};
  bool normals_is_read{false};
  
  std::regex vertices_pattern_{"-?\\b\\d+(\\.\\d+)?\\b(.*\\b-?\\d+(\\.\\d+)?\\b){2,3}"};
  std::regex textures_pattern {"-?\\b\\d+(\\.\\d+)?\\b.*-?\\b\\d+(\\.\\d+)?\\b"};
};
} // namespace s21

#endif
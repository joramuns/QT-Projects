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
#endif  // __APPLE__

#ifdef __linux__
#include <GL/glut.h>
#endif  // __linux__

#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "indices_pars/faces_strategy.h"
#include "packer/coordinate_packer.h"
#include "struct/coordinatestruct.h"

// for debug
#include <iostream>

namespace s21 {
class Parser {
 public:
  explicit Parser(const std::string &filename);

  ~Parser() = default;

  inline std::vector<std::vector<GLfloat>> GetCoordinates() const noexcept {
    return coordinates_;
  };
  bool GetReadStatus() const noexcept;
  bool GetTexturesStatus() const noexcept;
  bool GetNormalsStatus() const noexcept;
  int GetStride() const noexcept;

 private:
  bool IsCorrectFileFormat(const std::string &filename) const noexcept;
  bool IsFileExist(const std::string &filename) const noexcept;

  void DataRead(const std::string &filename) noexcept;

  int VertexRead(std::ifstream *file, int &file_position) noexcept;
  bool IsVertexData(const std::string &data) const noexcept;
  void VertexPointFill(const std::string &data) noexcept;

  int TexturesRead(std::ifstream *file, int &file_position) noexcept;
  bool IsTexturesData(const std::string &data) const noexcept;
  void TexturesPointFill(const std::string &data) noexcept;

  int NormalsRead(std::ifstream *file, int &file_position) noexcept;
  bool IsNormalsData(const std::string &data) const noexcept;
  void NormalsPointFill(const std::string &data) noexcept;

  void SetStrategy(std::ifstream *file, int &current_position) noexcept;
  void GetIndexes() noexcept;
  void ClearData() noexcept;
  /// @brief Сортирует и упаковывает данные в один вектор для дальнейшей
  /// отрисовки 3-х мерной модели в OpenGL
  void Packer() noexcept;

 private:
  std::vector<std::vector<GLfloat>> coordinates_;

  std::vector<GLfloat> vertices_;
  std::vector<std::vector<GLfloat>> all_vertices_;

  std::vector<GLfloat> textures_;
  std::vector<std::vector<GLfloat>> all_textures_;

  std::vector<GLfloat> normals_;
  std::vector<std::vector<GLfloat>> all_normals_;

  int vertices_is_read_{0};
  int textures_is_read_{0};
  int normals_is_read_{0};
  bool faces_is_read_{false};

  std::regex vertices_pattern_{
      "-?\\b\\d+(\\.\\d+)?\\b(.*\\b-?\\d+(\\.\\d+)?\\b){2,3}"};
  std::regex textures_pattern{"-?\\b\\d+(\\.\\d+)?\\b.*-?\\b\\d+(\\.\\d+)?\\b"};
  std::regex normals_pattern_{
      "-?\\b\\d+(\\.\\d+)?\\b.*-?\\b\\d+(\\.\\d+)?\\b.*-?\\b\\d+(\\.\\d+)?\\b"};

  FacesStrategy *face_parser_;

  /// @brief Вектор векторов индексов всех координат вершин для 3-х мерной
  /// модели
  std::vector<std::vector<GLint>> vertex_faces_;

  /// @brief Вектор векторов индексов всех координат текстур для 3-х мерной
  /// модели
  std::vector<std::vector<GLint>> texture_faces_;

  /// @brief Вектор векторов индексов всех координат нормалей для 3-х мерной
  /// модели
  std::vector<std::vector<GLint>> normal_faces_;
};
}  // namespace s21

#endif

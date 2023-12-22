#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_FACES_STRATEGY_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_FACES_STRATEGY_H
#include <OpenGL/gl.h>
// #include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class FacesStrategy {
public:
  FacesStrategy() = delete;
  FacesStrategy(std::ifstream *file, const int file_pos);
  virtual ~FacesStrategy(){};

  std::vector<GLint> GetVertices() const noexcept;
  std::vector<GLint> GetTextures() const noexcept;
  std::vector<GLint> GetNormals() const noexcept;

  virtual int Pars() = 0;

protected:
  void TesselationFill(const std::vector<GLint> &indexes,
                       std::vector<GLint> &type_of_indexes) noexcept;

protected:
  std::ifstream *file_;

  std::vector<GLint> vertices_;
  std::vector<GLint> texutres_;
  std::vector<GLint> normals_;

private:
};

class VertexStrategy : public FacesStrategy {
public:
  VertexStrategy(std::ifstream *file, const int file_pos);
  int Pars() noexcept override;
};

class VertexTexturesStrategy : public FacesStrategy {
public:
  VertexTexturesStrategy(std::ifstream *file, const int file_pos);
  int Pars() noexcept override;
};

class VertexNormalsStrategy : public FacesStrategy {
public:
  VertexNormalsStrategy(std::ifstream *file, const int file_pos);
  int Pars() noexcept override;
};

class VertexTexturesNormalsStrategy : public FacesStrategy {
public:
  VertexTexturesNormalsStrategy(std::ifstream *file, const int file_pos);
  int Pars() noexcept override;
};

} // namespace s21
#endif // CPP4_3DVIEWER_V2_MODEL_PARSER_FACES_STRATEGY_H
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

  std::vector<GLuint> GetVertices() const noexcept;
  std::vector<GLuint> GetTextures() const noexcept;
  std::vector<GLuint> GetNormals() const noexcept;

  virtual int Pars() noexcept = 0;

protected:
  void TesselationFill(const std::vector<GLuint> &indexes,
                       std::vector<GLuint> &type_of_indexes) noexcept;

protected:
  std::ifstream *file_;

  std::vector<GLuint> vertices_;
  std::vector<GLuint> texutres_;
  std::vector<GLuint> normals_;

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
#include <OpenGL/gl.h>
// #include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "coordinatecontain.h"

namespace s21 {
class FacesStrategy {
public:
  FacesStrategy() = delete;
  FacesStrategy(std::ifstream *file, const int file_pos,
                const CoordinateContain &contain);
  virtual ~FacesStrategy(){};

  std::vector<GLfloat> GetVertices();
  std::vector<GLfloat> GetTextures();
  std::vector<GLfloat> GetNormals();

  virtual int Pars() noexcept = 0;

protected:
  void PointFill(const int index) noexcept;
  void TexturesFill(const int index) noexcept;
  void NormalsFill(const int index) noexcept;

protected:
  std::ifstream *file_;
  CoordinateContain container_;
  std::vector<GLfloat> vertices_;
  std::vector<GLfloat> texutres_;
  std::vector<GLfloat> normals_;
};

class VertexStrategy : public FacesStrategy {
public:
  VertexStrategy(std::ifstream *file, const int file_pos,
                 const CoordinateContain &contain);
  int Pars() noexcept override;
};

class VertexTexturesStrategy : public FacesStrategy {
public:
  VertexTexturesStrategy(std::ifstream *file, const int file_pos,
                         const CoordinateContain &contain);
  int Pars() noexcept override;
};

class VertexNormalsStrategy : public FacesStrategy {
public:
  VertexNormalsStrategy(std::ifstream *file, const int file_pos,
                        const CoordinateContain &contain);
  int Pars() noexcept override;
};

class VertexTexturesNormalsStrategy : public FacesStrategy {
public:
  VertexTexturesNormalsStrategy(std::ifstream *file, const int file_pos,
                                const CoordinateContain &contain);
  int Pars() noexcept override;
};

} // namespace s21
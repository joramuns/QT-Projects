// #include <OpenGL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class FacesStrategy {
public:
  FacesStrategy() = delete;
  FacesStrategy(std::ifstream *file, int file_pos);
  virtual ~FacesStrategy(){};

  std::vector<GLfloat> GetVertices();
  std::vector<GLfloat> GetTextures();
  std::vector<GLfloat> GetNormals();

  virtual void Pars() noexcept = 0;

protected:
  std::ifstream *file_;
  // int file_position_;
  std::vector<GLfloat> vertices_;
  std::vector<GLfloat> texutres_;
  std::vector<GLfloat> normals_;
};

class VertexStrategy : public FacesStrategy {
  public:
  VertexStrategy(std::ifstream *file, int file_pos);
  void Pars() noexcept override;
};

class VertexTexturesStrategy: public FacesStrategy {
  public:
  VertexTexturesStrategy(std::ifstream *file, int file_pos);
  void Pars() noexcept override;
};

class VertexNormalsStrategy: public FacesStrategy {
  public:
  VertexNormalsStrategy(std::ifstream *file, int file_pos);
  void Pars() noexcept override;
};

class VertexTexturesNormalsStrategy: public FacesStrategy {

};

} // namespace s21
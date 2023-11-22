#include <OpenGL/gl.h>
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

private:
  virtual void Pars() = 0;

protected:
  std::ifstream *file_;
  int file_position_;
  std::vector<GLfloat> vertices_;
  std::vector<GLfloat> texutres_;
  std::vector<GLfloat> normals_;
};

class VertexStrategy : public FacesStrategy {
  public:
  explicit VertexStrategy(std::ifstream *file, int file_pos);
  
  private:
  void Pars() override;

};

class VertexTexturesStrategy: public FacesStrategy {

};

class VertexNormalsStrategy: public FacesStrategy {

};

class VertexTexturesNormalsStrategy: public FacesStrategy {

};

} // namespace s21
#include "faces_strategy.h"

namespace s21 {
FacesStrategy::FacesStrategy(std::ifstream *file, int file_pos) : file_(file) {
  file_->seekg(file_pos);
};

std::vector<GLfloat> FacesStrategy::GetVertices() { return vertices_; };

std::vector<GLfloat> FacesStrategy::GetTextures() { return texutres_; };

std::vector<GLfloat> FacesStrategy::GetNormals() { return normals_; };

VertexStrategy::VertexStrategy(std::ifstream *file, int file_pos)
    : FacesStrategy(file, file_pos){};

void VertexStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::istringstream data(line.substr(2));
    int x;
    data >> x;
    int y;
    data >> y;
    int z;
    data >> z;
    std::cout << x << " | " << y << " | " << z << std::endl;
  }
};

VertexTexturesStrategy::VertexTexturesStrategy(std::ifstream *file,
                                               int file_pos)
    : FacesStrategy(file, file_pos){};

void VertexTexturesStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int x;
      data >> x;
      data.get();
      int xt;
      data >> xt;
      std::cout << x << " | " << xt << std::endl;
      data.get();
    }
  }
}

VertexNormalsStrategy::VertexNormalsStrategy(std::ifstream *file, int file_pos)
    : FacesStrategy(file, file_pos){};

void VertexNormalsStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int x;
      data >> x;
      data.get();
      data.get();
      int xn;
      data >> xn;
      std::cout << x << " | " << xn << std::endl;
      data.get();
    }
  }
}

} // namespace s21
#include "faces_strategy.h"

namespace s21 {
FacesStrategy::FacesStrategy(std::ifstream *file, const int file_pos)
    : file_(file) {
  file_->seekg(file_pos);
};

std::vector<GLfloat> FacesStrategy::GetVertices() { return vertices_; };

std::vector<GLfloat> FacesStrategy::GetTextures() { return texutres_; };

std::vector<GLfloat> FacesStrategy::GetNormals() { return normals_; };

VertexStrategy::VertexStrategy(std::ifstream *file, const int file_pos)
    : FacesStrategy(file, file_pos){};

void VertexStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      std::cout << v << std::endl;
      data.get();
    }
  }
};

VertexTexturesStrategy::VertexTexturesStrategy(std::ifstream *file,
                                               const int file_pos)
    : FacesStrategy(file, file_pos){};

void VertexTexturesStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      data.get();
      int vt;
      data >> vt;
      std::cout << v << " | " << vt << std::endl;
      data.get();
    }
  }
}

VertexNormalsStrategy::VertexNormalsStrategy(std::ifstream *file,
                                             const int file_pos)
    : FacesStrategy(file, file_pos){};

void VertexNormalsStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      data.get();
      data.get();
      int vn;
      data >> vn;
      std::cout << v << " | " << vn << std::endl;
      data.get();
    }
  }
}

VertexTexturesNormalsStrategy::VertexTexturesNormalsStrategy(
    std::ifstream *file, const int file_pos)
    : FacesStrategy(file, file_pos){};

void VertexTexturesNormalsStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line))  {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      data.get();
      int vt;
      data >> vt;
      data.get();
      int vn;
      data >> vn;
      std::cout << v << " | " << vt << " | " << vn << std::endl;
      data.get();
    }
  }
  
}

} // namespace s21
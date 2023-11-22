#include "faces_strategy.h"

namespace s21 {
FacesStrategy::FacesStrategy(std::ifstream *file, int file_pos)
    : file_(file), file_position_(file_pos){};

std::vector<GLfloat> FacesStrategy::GetVertices() { return vertices_; };

std::vector<GLfloat> FacesStrategy::GetTextures() { return texutres_; };

std::vector<GLfloat> FacesStrategy::GetNormals() { return normals_; };

VertexStrategy::VertexStrategy(std::ifstream *file, int file_pos)
    : FacesStrategy(file, file_pos){};

void VertexStrategy::Pars() {
  std::string line;
  file_->seekg(file_position_);
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

VertexTexturesStrategy::VertexTexturesStrategy(std::ifstream *file, int file_pos) : FacesStrategy(file, file_pos){};

void VertexTexturesStrategy::Pars() {
  std::string line;
  file_->seekg(file_position_);
  while (std::getline(*file_, line)) {
    std::istringstream data(line.substr(2));
    char bebra;
    int x;
    data >> x;
    data >> bebra;
    int xt;
    data >> xt;
    int y;
    data >> y;
    data >> bebra;
    int yt;
    data >> yt;
    int z;
    data >> z;
    data >> bebra;
    int zt;
    data >> zt;
    std::cout << x << " | " << xt << " | " << y << " | " << yt << " | " << z << " | " << zt << std::endl;
  }
}

} // namespace s21
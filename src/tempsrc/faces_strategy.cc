#include "faces_strategy.h"

namespace s21 {
FacesStrategy::FacesStrategy(std::ifstream *file, int file_pos)
    : file_(file), file_position_(file_pos){};

std::vector<GLfloat> FacesStrategy::GetVertices() { return vertices_; };

std::vector<GLfloat> FacesStrategy::GetTextures() { return texutres_; };

std::vector<GLfloat> FacesStrategy::GetNormals() { return normals_; };

VertexStrategy::VertexStrategy(std::ifstream *file, int file_pos)
    : FacesStrategy(file, file_pos) {
  Pars();
};

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
}

} // namespace s21
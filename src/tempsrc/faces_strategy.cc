#include "faces_strategy.h"

namespace s21 {
FacesStrategy::FacesStrategy(std::ifstream *file, const int file_pos,
                             const CoordinateContain &contain)
    : file_(file), container_(contain) {
  file_->seekg(file_pos);
};

std::vector<GLfloat> FacesStrategy::GetVertices() { return vertices_; };

std::vector<GLfloat> FacesStrategy::GetTextures() { return texutres_; };

std::vector<GLfloat> FacesStrategy::GetNormals() { return normals_; };

void FacesStrategy::PointFill(const int index) noexcept {
  PointCoordinates cord = container_.GetPointCoordinates(index);
  vertices_.push_back(cord.x);
  vertices_.push_back(cord.y);
  vertices_.push_back(cord.z);
  vertices_.push_back(cord.a);
}

void FacesStrategy::TexturesFill(const int index) noexcept {
  TexturesCoordinates cord = container_.GetTexturesCoordinates(index);
  texutres_.push_back(cord.u);
  texutres_.push_back(cord.v);
  texutres_.push_back(cord.w);
}

void FacesStrategy::NormalsFill(const int index) noexcept {
  NormalsCoordinate cord = container_.GetNormalsCoordinates(index);
  normals_.push_back(cord.x);
  normals_.push_back(cord.y);
  normals_.push_back(cord.z);
}

VertexStrategy::VertexStrategy(std::ifstream *file, const int file_pos,
                               const CoordinateContain &contain)
    : FacesStrategy(file, file_pos, contain){};

void VertexStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      PointFill(v);
      data.get();
    }
  }
};

VertexTexturesStrategy::VertexTexturesStrategy(std::ifstream *file,
                                               const int file_pos,
                                               const CoordinateContain &contain)
    : FacesStrategy(file, file_pos, contain){};

void VertexTexturesStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      PointFill(v);
      data.get();
      int vt;
      data >> vt;
      TexturesFill(vt);
      data.get();
    }
  }
}

VertexNormalsStrategy::VertexNormalsStrategy(std::ifstream *file,
                                             const int file_pos,
                                             const CoordinateContain &contain)
    : FacesStrategy(file, file_pos, contain){};

void VertexNormalsStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      PointFill(v);
      data.get();
      data.get();
      int vn;
      data >> vn;
      NormalsFill(vn);
      data.get();
    }
  }
}

VertexTexturesNormalsStrategy::VertexTexturesNormalsStrategy(
    std::ifstream *file, const int file_pos, const CoordinateContain &contain)
    : FacesStrategy(file, file_pos, contain){};

void VertexTexturesNormalsStrategy::Pars() noexcept {
  std::string line;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    std::istringstream data(line.substr(2));
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      PointFill(v);
      data.get();
      int vt;
      data >> vt;
      TexturesFill(vt);
      data.get();
      int vn;
      data >> vn;
      NormalsFill(vn);
      data.get();
    }
  }
}

} // namespace s21
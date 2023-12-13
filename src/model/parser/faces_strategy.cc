#include "faces_strategy.h"

namespace s21 {
FacesStrategy::FacesStrategy(std::ifstream *file, const int file_pos)
    : file_(file) {
  file_->seekg(file_pos);
};

std::vector<GLuint> FacesStrategy::GetVertices() const noexcept {
  return vertices_;
};

std::vector<GLuint> FacesStrategy::GetTextures() const noexcept {
  return texutres_;
};

std::vector<GLuint> FacesStrategy::GetNormals() const noexcept {
  return normals_;
};

void FacesStrategy::TesselationFill(
    const std::vector<GLuint> &indexes,
    std::vector<GLuint> &type_of_indexes) noexcept {
  for (size_t i = 0; i < indexes.size(); ++i) {
    if (i > 2) {
      type_of_indexes.push_back(indexes[0] - 1);
      type_of_indexes.push_back(indexes[i - 1] - 1);
    }
    type_of_indexes.push_back(indexes[i] - 1);
  }
};

VertexStrategy::VertexStrategy(std::ifstream *file, const int file_pos)
    : FacesStrategy(file, file_pos){};

int VertexStrategy::Pars() noexcept {
  std::string line;
  int position = -1;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    if (prefix == "v ")
      break;
    std::istringstream data(line.substr(2));
    std::vector<GLuint> v_tmp;
    while (data.peek() != EOF && prefix == "f ") {
      GLuint v;
      data >> v;
      v_tmp.push_back(v);
      data.get();
    }
    TesselationFill(v_tmp, vertices_);
    position = file_->tellg();
  }
  return position;
};

VertexTexturesStrategy::VertexTexturesStrategy(std::ifstream *file,
                                               const int file_pos)
    : FacesStrategy(file, file_pos){};

int VertexTexturesStrategy::Pars() noexcept {
  std::string line;
  int position = -1;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    if (prefix == "v ")
      break;
    std::istringstream data(line.substr(2));
    std::vector<GLuint> v_tmp;
    std::vector<GLuint> vt_tmp;
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      v_tmp.push_back(v);
      data.get();
      int vt;
      data >> vt;
      vt_tmp.push_back(vt);
      data.get();
    }
    TesselationFill(v_tmp, vertices_);
    TesselationFill(vt_tmp, texutres_);
    position = file_->tellg();
  }
  return position;
}

VertexNormalsStrategy::VertexNormalsStrategy(std::ifstream *file,
                                             const int file_pos)
    : FacesStrategy(file, file_pos){};

int VertexNormalsStrategy::Pars() noexcept {
  std::string line;
  int position = -1;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    if (prefix == "v ")
      break;
    std::istringstream data(line.substr(2));
    std::vector<GLuint> v_tmp;
    std::vector<GLuint> vn_tmp;
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      v_tmp.push_back(v);
      data.get();
      data.get();
      int vn;
      data >> vn;
      vn_tmp.push_back(vn);
      data.get();
    }
    TesselationFill(v_tmp, vertices_);
    TesselationFill(vn_tmp, normals_);
    position = file_->tellg();
  }
  return position;
}

VertexTexturesNormalsStrategy::VertexTexturesNormalsStrategy(
    std::ifstream *file, const int file_pos)
    : FacesStrategy(file, file_pos){};

int VertexTexturesNormalsStrategy::Pars() noexcept {
  std::string line;
  int position = -1;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    if (prefix == "v ")
      break;
    std::istringstream data(line.substr(2));
    std::vector<GLuint> v_tmp;
    std::vector<GLuint> vt_tmp;
    std::vector<GLuint> vn_tmp;
    while (data.peek() != EOF && prefix == "f ") {
      int v;
      data >> v;
      v_tmp.push_back(v);
      data.get();
      int vt;
      data >> vt;
      vt_tmp.push_back(vt);
      data.get();
      int vn;
      data >> vn;
      vn_tmp.push_back(vn);
      data.get();
    }
    TesselationFill(v_tmp, vertices_);
    TesselationFill(vt_tmp, texutres_);
    TesselationFill(vn_tmp, normals_);
    position = file_->tellg();
  }

  return position;
}

} // namespace s21

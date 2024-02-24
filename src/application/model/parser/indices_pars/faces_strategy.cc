#include "faces_strategy.h"

namespace s21 {
FacesStrategy::FacesStrategy(std::ifstream *file, int &file_pos)
    : file_(file), file_position_(file_pos) {
  file_->seekg(file_pos);
};

std::vector<GLint> FacesStrategy::GetVertices() const noexcept {
  return vertices_;
};

std::vector<GLint> FacesStrategy::GetTextures() const noexcept {
  return texutres_;
};

std::vector<GLint> FacesStrategy::GetNormals() const noexcept {
  return normals_;
};

void FacesStrategy::TesselationFill(
    const std::vector<GLint> &indexes,
    std::vector<GLint> &type_of_indexes) noexcept {
  for (size_t i = 0; i < indexes.size(); ++i) {
    if (i > 2) {
      type_of_indexes.push_back(indexes[0] - 1);
      type_of_indexes.push_back(indexes[i - 1] - 1);
    }
    type_of_indexes.push_back(indexes[i] - 1);
  }
};

VertexStrategy::VertexStrategy(std::ifstream *file, int &file_pos)
    : FacesStrategy(file, file_pos){};

bool VertexStrategy::Pars() noexcept {
  bool result{true};
  std::string data_line;
  while (std::getline(*file_, data_line) && data_line.substr(0, 2) == "f ") {
    std::vector<GLint> v_tmp;
    if (IsValid(data_line)) {
      IndicesFill(v_tmp, data_line);
    } else {
      result = false;
    }
    TesselationFill(v_tmp, vertices_);
    file_position_ = file_->tellg();
  }
  return result;
};

bool VertexStrategy::IsValid(const std::string &data_line) const noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  return std::regex_search(data_line, pattern);
}

void VertexStrategy::IndicesFill(std::vector<GLint> &v_tmp,
                                 const std::string &data) const noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  while (it != end) {
    v_tmp.push_back(std::stoi(it->str()));
    ++it;
  }
}

VertexTexturesStrategy::VertexTexturesStrategy(std::ifstream *file,
                                               int &file_pos)
    : FacesStrategy(file, file_pos){};

bool VertexTexturesStrategy::Pars() noexcept {
  std::string line;
  int position = -1;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    if (prefix == "v ")
      break;
    std::istringstream data(line.substr(2));
    std::vector<GLint> v_tmp;
    std::vector<GLint> vt_tmp;
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

VertexNormalsStrategy::VertexNormalsStrategy(std::ifstream *file, int &file_pos)
    : FacesStrategy(file, file_pos){};

int VertexNormalsStrategy::Pars() noexcept {
  std::string line;
  int position = -1;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    if (prefix == "v ")
      break;
    std::istringstream data(line.substr(2));
    std::vector<GLint> v_tmp;
    std::vector<GLint> vn_tmp;
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
    std::ifstream *file, int &file_pos)
    : FacesStrategy(file, file_pos){};

int VertexTexturesNormalsStrategy::Pars() noexcept {
  std::string line;
  int position = -1;
  while (std::getline(*file_, line)) {
    std::string prefix = line.substr(0, 2);
    if (prefix == "v ")
      break;
    std::istringstream data(line.substr(2));
    std::vector<GLint> v_tmp;
    std::vector<GLint> vt_tmp;
    std::vector<GLint> vn_tmp;
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

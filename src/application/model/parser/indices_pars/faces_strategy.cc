#include "faces_strategy.h"

namespace s21 {
FacesStrategy::FacesStrategy(std::ifstream *file, int &current_position)
    : file_(file), current_positionition_(current_position) {
  file_->seekg(current_position);
};

bool FacesStrategy::IsValid(const std::string &data_line) const noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  return std::regex_search(data_line, pattern);
}

std::vector<GLint> FacesStrategy::GetVertices() const noexcept {
  return vertices_;
};

std::vector<GLint> FacesStrategy::GetTextures() const noexcept {
  return textures_;
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

VertexStrategy::VertexStrategy(std::ifstream *file, int &current_position)
    : FacesStrategy(file, current_position){};

bool VertexStrategy::Pars() noexcept {
  bool result{true};
  std::string data_line;
  while (std::getline(*file_, data_line)) {
    if (data_line.substr(0, 2) == "f ") {
      std::vector<GLint> v_tmp;
      if (IsValid(data_line)) {
        IndicesFill(v_tmp, data_line);
      } else {
        result = false;
      }
      TesselationFill(v_tmp, vertices_);
      current_positionition_ = file_->tellg();
    }
  }
  if (result) {
    result = IsSuccess();
  }
  return result;
};

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

bool VertexStrategy::IsSuccess() const noexcept { return (!vertices_.empty()); }

VertexTexturesStrategy::VertexTexturesStrategy(std::ifstream *file,
                                               int &current_position)
    : FacesStrategy(file, current_position){};

bool VertexTexturesStrategy::Pars() noexcept {
  bool result{true};
  std::string data_line;
  while (std::getline(*file_, data_line) && data_line.substr(0, 2) == "f ") {
    if (data_line.substr(0, 2) == "f ") {
      std::vector<GLint> v_tmp;
      std::vector<GLint> vt_tmp;
      if (IsValid(data_line)) {
        IndicesFill(v_tmp, vt_tmp, data_line);
      } else {
        result = false;
      }
      TesselationFill(v_tmp, vertices_);
      TesselationFill(vt_tmp, textures_);
      current_positionition_ = file_->tellg();
    }
  }
  if (result) {
    result = IsSuccess();
  }
  return result;
}

void VertexTexturesStrategy::IndicesFill(
    std::vector<GLint> &v_tmp, std::vector<GLint> &vt_tmp,
    const std::string &data) const noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  while (it != end) {
    v_tmp.push_back(std::stoi(it->str()));
    ++it;
    if (it != end) {
      vt_tmp.push_back(std::stoi(it->str()));
      ++it;
    }
  }
}

bool VertexTexturesStrategy::IsSuccess() const noexcept {
  bool condition_one = (!vertices_.empty() && !textures_.empty());
  bool condition_two = (vertices_.size() == textures_.size());
  return (condition_one && condition_two);
}

VertexNormalsStrategy::VertexNormalsStrategy(std::ifstream *file,
                                             int &current_position)
    : FacesStrategy(file, current_position){};

bool VertexNormalsStrategy::Pars() noexcept {
  bool result{true};
  std::string data_line;
  while (std::getline(*file_, data_line) && data_line.substr(0, 2) == "f ") {
    if (data_line.substr(0, 2) == "f ") {
      std::vector<GLint> v_tmp;
      std::vector<GLint> vn_tmp;
      if (IsValid(data_line)) {
        IndicesFill(v_tmp, vn_tmp, data_line);
      } else {
        result = false;
      }
      TesselationFill(v_tmp, vertices_);
      TesselationFill(vn_tmp, normals_);
      current_positionition_ = file_->tellg();
    }
  }
  if (result) {
    result = IsSuccess();
  }
  return result;
}

void VertexNormalsStrategy::IndicesFill(
    std::vector<GLint> &v_tmp, std::vector<GLint> &vn_tmp,
    const std::string &data) const noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  while (it != end) {
    v_tmp.push_back(std::stoi(it->str()));
    ++it;
    if (it != end) {
      vn_tmp.push_back(std::stoi(it->str()));
      ++it;
    }
  }
}

bool VertexNormalsStrategy::IsSuccess() const noexcept {
  bool condition_one = (!vertices_.empty() && !normals_.empty());
  bool condition_two = (vertices_.size() && normals_.size());
  return (condition_one && condition_two);
}

VertexTexturesNormalsStrategy::VertexTexturesNormalsStrategy(
    std::ifstream *file, int &current_position)
    : FacesStrategy(file, current_position){};

bool VertexTexturesNormalsStrategy::Pars() noexcept {
  bool result{true};
  std::string data_line;
  while (std::getline(*file_, data_line) && data_line.substr(0, 2) == "f ") {
    if (data_line.substr(0, 2) == "f ") {
      std::vector<GLint> v_tmp;
      std::vector<GLint> vt_tmp;
      std::vector<GLint> vn_tmp;
      if (IsValid(data_line)) {
        IndicesFill(v_tmp, vt_tmp, vn_tmp, data_line);
      } else {
        result = false;
      }
      TesselationFill(v_tmp, vertices_);
      TesselationFill(vt_tmp, textures_);
      TesselationFill(vn_tmp, normals_);
      current_positionition_ = file_->tellg();
    }
  }
  if (result) {
    result = IsSuccess();
  }
  return result;
}

void VertexTexturesNormalsStrategy::IndicesFill(
    std::vector<GLint> &v_tmp, std::vector<GLint> &vt_tmp,
    std::vector<GLint> &vn_tmp, const std::string &data) const noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  while (it != end) {
    v_tmp.push_back(std::stoi(it->str()));
    ++it;
    if (it != end) {
      vt_tmp.push_back(std::stoi(it->str()));
      ++it;
    }
    if (it != end) {
      vn_tmp.push_back(std::stoi(it->str()));
      ++it;
    }
  }
}

bool VertexTexturesNormalsStrategy::IsSuccess() const noexcept {
  bool condition_one =
      (!vertices_.empty() && !textures_.empty() && !normals_.empty());
  bool condition_two = (vertices_.size() == textures_.size() &&
                        vertices_.size() == normals_.size());
  return (condition_one && condition_two);
}

} // namespace s21

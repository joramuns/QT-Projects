#include "new-parser.h"

namespace s21 {

NewParser::NewParser(const std::string &filename) {
  if (!IsCorrectFileFormat(filename)) {
    throw std::invalid_argument("\n Invalid file format");
  } else if (!IsFileExist(filename)) {
    throw std::invalid_argument("\n File does not exist");
  } else {
    DataRead(filename);
  }
}

bool NewParser::IsCorrectFileFormat(
    const std::string &filename) const noexcept {
  return (filename.substr(filename.length() - 3, 3) == "obj");
}

bool NewParser::IsFileExist(const std::string &filename) const noexcept {
  bool result = true;
  std::ifstream file;
  file.open(filename, std::ios::in);
  if (!file) {
    result = false;
  } else {
    file.close();
  }
  return result;
}

void NewParser::DataRead(const std::string &filename) noexcept {
  std::ifstream file;
  file.open(filename, std::ios::in);
  std::string line;
  int file_position;
  while (std::getline(file, line)) {
    if (line.size() < 3) {
      file_position = file.tellg();
    } else {
      std::string prefix = line.substr(0, 2);
      if (prefix == "v ") {
        vertices_is_read_ = VertexRead(&file, file_position);
        file.seekg(file_position);
      } else if (prefix == "vt" && vertices_is_read_) {
        textures_is_read_ = TexturesRead(&file, file_position);
        file.seekg(file_position);
      } else if (prefix == "vn" && vertices_is_read_) {
        normals_is_read_ = NormalsRead(&file, file_position);
        file.seekg(file_position);
      } else if (prefix == "f " && vertices_is_read_) {
        SetStrategy(&file, file_position);
      }
      file_position = file.tellg();
    }
  }
  file.close();
}

bool NewParser::VertexRead(std::ifstream *file, int &file_position) noexcept {
  bool result = true;
  file->seekg(file_position);
  std::string data_line;
  std::getline(*file, data_line);
  std::string prefix = data_line.substr(0, 2);
  while (prefix == "v ") {
    if (IsVertexData(data_line)) {
      VertexPointFill(data_line);
    } else {
      result = false;
    }
    std::getline(*file, data_line);
    file_position = file->tellg();
    prefix = data_line.substr(0, 2);
  }
  if (result) {
    all_vertices_.push_back(vertices_);
  } else {
    vertices_.clear();
  }
  return result;
}

bool NewParser::IsVertexData(const std::string &data) const noexcept {
  return std::regex_search(data, vertices_pattern_);
}

void NewParser::VertexPointFill(const std::string &data) noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  for (int i = 0; i < 4; ++i) {
    if (it != end) {
      double coordinate = std::stod(it->str());
      if (i == 3 && (coordinate > 1 || coordinate < 0)) {
        vertices_.push_back(1);
      } else {
        vertices_.push_back(std::stod(it->str()));
        ++it;
      }
    } else {
      vertices_.push_back(1);
    }
  }
}

bool NewParser::TexturesRead(std::ifstream *file, int &file_position) noexcept {
  bool result = true;
  file->seekg(file_position);
  std::string data_line;
  std::getline(*file, data_line);
  std::string prefix = data_line.substr(0, 2);
  while (prefix == "vt") {
    if (IsTexturesData(data_line)) {
      TexturesPointFill(data_line);
    } else {
      result = false;
    }
    std::getline(*file, data_line);
    file_position = file->tellg();
    prefix = data_line.substr(0, 2);
  }
  if (result) {
    all_textures_.push_back(textures_);
  } else {
    textures_.clear();
  }
  return result;
}

bool NewParser::IsTexturesData(const std::string &data) const noexcept {
  return std::regex_search(data, textures_pattern);
}

void NewParser::TexturesPointFill(const std::string &data) noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  while (it != end) {
    textures_.push_back(std::stod(it->str()));
    ++it;
  }
}

bool NewParser::NormalsRead(std::ifstream *file, int &file_position) noexcept {
  bool result = true;
  file->seekg(file_position);
  std::string data_line;
  std::getline(*file, data_line);
  std::string prefix = data_line.substr(0, 2);
  while (prefix == "vn") {
    if (IsNormalsData(data_line)) {
      NormalsPointFill(data_line);
    } else {
      result = false;
    }
    std::getline(*file, data_line);
    file_position = file->tellg();
    prefix = data_line.substr(0, 2);
  }
  if (result) {
    all_normals_.push_back(normals_);
  } else {
    normals_.clear();
  }
  return result;
}

bool NewParser::IsNormalsData(const std::string &data) const noexcept {
  return std::regex_search(data, normals_pattern_);
}

void NewParser::NormalsPointFill(const std::string &data) noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  while (it != end) {
    normals_.push_back(std::stod(it->str()));
    ++it;
  }
}

void NewParser::SetStrategy(std::ifstream *file, int current_position) noexcept {
  if (!textures_is_read_ && !normals_is_read_) {
    face_parser_ = new VertexStrategy(file, current_position);
  } else if (textures_is_read_ && !normals_is_read_) {
    face_parser_ = new VertexTexturesStrategy(file, current_position);
  } else if (!textures_is_read_ && normals_is_read_) {
    face_parser_ = new VertexNormalsStrategy(file, current_position);
  } else {
    face_parser_ = new VertexTexturesNormalsStrategy(file, current_position);
  }
}

} // namespace s21
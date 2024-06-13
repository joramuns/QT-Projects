#include "parser.h"

namespace s21 {

Parser::Parser(const std::string &filename) {
  if (!IsCorrectFileFormat(filename)) {
    throw std::invalid_argument("\n Invalid file format");
  } else if (!IsFileExist(filename)) {
    throw std::invalid_argument("\n File does not exist");
  } else {
    DataRead(filename);
    for (const auto &elem : all_vertices_) {
      vert_number_ += elem.size() / 4;
    }
    for (const auto &elem : vertex_faces_) {
      edge_number_ += elem.size();
    }
    if (vertices_is_read_ && faces_is_read_) {
      Packer();
    }
  }
}

bool Parser::IsCorrectFileFormat(const std::string &filename) const noexcept {
  return (filename.substr(filename.length() - 3, 3) == "obj");
}

bool Parser::IsFileExist(const std::string &filename) const noexcept {
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

void Parser::DataRead(const std::string &filename) noexcept {
  std::ifstream file;
  file.open(filename, std::ios::in);
  std::string line;
  int file_position = 0;
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
        file.seekg(file_position);
        if (face_parser_->Pars()) {
          faces_is_read_ = true;
          GetIndexes();
        } else {
          ClearData();
        }
      }
      file_position = file.tellg();
    }
  }
  file.close();
}

int Parser::VertexRead(std::ifstream *file, int &file_position) noexcept {
  int result = 4;
  file->seekg(file_position);
  std::string data_line;
  std::getline(*file, data_line);
  std::string prefix = data_line.substr(0, 2);
  while (prefix == "v ") {
    if (IsVertexData(data_line)) {
      VertexPointFill(data_line);
    } else {
      result = 0;
    }
    if (std::getline(*file, data_line)) {
      prefix = data_line.substr(0, 2);
      if (prefix == "v " || data_line.size() == 1) {
        file_position = file->tellg();
      }
    } else {
      break;
    }
  }
  if (result) {
    all_vertices_.push_back(vertices_);
    vertices_.clear();
  } else {
    vertices_.clear();
  }
  return result;
}

bool Parser::IsVertexData(const std::string &data) const noexcept {
  return std::regex_search(data, vertices_pattern_);
}

void Parser::VertexPointFill(const std::string &data) noexcept {
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

int Parser::TexturesRead(std::ifstream *file, int &file_position) noexcept {
  int result = 2;
  file->seekg(file_position);
  std::string data_line;
  std::getline(*file, data_line);
  std::string prefix = data_line.substr(0, 2);
  while (prefix == "vt") {
    if (IsTexturesData(data_line)) {
      TexturesPointFill(data_line);
    } else {
      result = 0;
    }
    if (std::getline(*file, data_line)) {
      prefix = data_line.substr(0, 2);
      if (prefix == "vt" || data_line.size() == 1) {
        file_position = file->tellg();
      }
    } else {
      break;
    }
  }
  if (result) {
    all_textures_.push_back(textures_);
    textures_.clear();
  } else {
    textures_.clear();
  }
  return result;
}

bool Parser::IsTexturesData(const std::string &data) const noexcept {
  return std::regex_search(data, textures_pattern);
}

void Parser::TexturesPointFill(const std::string &data) noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  while (it != end) {
    textures_.push_back(std::stod(it->str()));
    ++it;
  }
}

int Parser::NormalsRead(std::ifstream *file, int &file_position) noexcept {
  int result = 3;
  file->seekg(file_position);
  std::string data_line;
  std::getline(*file, data_line);
  std::string prefix = data_line.substr(0, 2);
  while (prefix == "vn") {
    if (IsNormalsData(data_line)) {
      NormalsPointFill(data_line);
    } else {
      result = 0;
    }
    if (std::getline(*file, data_line)) {
      prefix = data_line.substr(0, 2);
      if (prefix == "vn" || data_line.size() == 1) {
        file_position = file->tellg();
      }
    } else {
      break;
    }
  }
  if (result) {
    all_normals_.push_back(normals_);
    normals_.clear();
  } else {
    normals_.clear();
  }
  return result;
}

bool Parser::IsNormalsData(const std::string &data) const noexcept {
  return std::regex_search(data, normals_pattern_);
}

void Parser::NormalsPointFill(const std::string &data) noexcept {
  std::regex pattern("-?\\b\\d+(\\.\\d+)?\\b");
  std::regex_iterator<std::string::const_iterator> it(data.begin(), data.end(),
                                                      pattern);
  std::regex_iterator<std::string::const_iterator> end;
  while (it != end) {
    normals_.push_back(std::stod(it->str()));
    ++it;
  }
}

void Parser::SetStrategy(std::ifstream *file, int &current_position) noexcept {
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

void Parser::GetIndexes() noexcept {
  vertex_faces_.push_back(face_parser_->GetVertices());
  texture_faces_.push_back(face_parser_->GetTextures());
  normal_faces_.push_back(face_parser_->GetNormals());
  ClearData();
}

void Parser::ClearData() noexcept {
  if (face_parser_ != nullptr) {
    delete face_parser_;
  }
}

void Parser::Packer() noexcept {
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLint>>>
      vertices{all_vertices_, vertex_faces_};
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLint>>>
      normals{all_normals_, normal_faces_};
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLint>>>
      textures{all_textures_, texture_faces_};

  CoordinatePacker *packer = nullptr;

  if (!textures_is_read_ && !normals_is_read_) {  // v
    packer = new VertexCoordinatePacker(vertices);
  } else if (textures_is_read_ && !normals_is_read_) {  // v/vt
    packer = new VertexTexturesCoordinatePacker(vertices, textures);
  } else if (!textures_is_read_ && normals_is_read_) {  // v//vn
    packer = new VertexNormalsCoordinatePacker(vertices, normals);
  } else {
    packer =
        new VertexTexturesNormalsCoordinatePacker(vertices, textures, normals);
  }
  coordinates_ = packer->GetCoordinates();

  delete packer;
}

bool Parser::GetReadStatus() const noexcept { return !coordinates_.empty(); }

bool Parser::GetTexturesStatus() const noexcept { return textures_is_read_; }

bool Parser::GetNormalsStatus() const noexcept { return normals_is_read_; }

int Parser::GetStride() const noexcept {
  return vertices_is_read_ + normals_is_read_ + textures_is_read_;
}

}  // namespace s21

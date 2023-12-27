#include "parser.h"

namespace s21 {
Parser::Parser(const std::string &filename) {
  ReadObj(filename);
  Packer();
};

Parser::~Parser(){};

std::vector<std::vector<GLfloat>> Parser::GetCoordinates() const noexcept {
  return coordinates_;
};

// std::vector<std::vector<GLint>> Parser::GetNormalIndexes() const noexcept {
//   return normal_faces_;
// };

/* Private functions */
int Parser::ReadObj(const std::string &filename) {
  std::ifstream file;
  file.open(filename, std::ios::in);
  std::string line;
  if (!file) {
    return BAD_FILENAME;
  } else {
    int file_position;
    while (std::getline(file, line)) {
      if (line.size() < 3) {
        std::cout << "BEBRA" << std::endl;
        continue;
      }
      std::string prefix = line.substr(0, 2);
      std::istringstream data(line.substr(2));
      if (prefix == "v ") {
        AddPoint(data);
      } else if (prefix == "vt") {
        AddTexturePoint(data);
      } else if (prefix == "vn") {
        AddNormalsPoint(data);
      } else if (prefix == "f ") {
        AddPointInArray();
        SetStrategy(&file, file_position);
        file.seekg(faces_pars_->Pars());
        GetIndexes();
        DataClear();
      }
      file_position = file.tellg();
    }
  }
  // DebugPrint();
  Packer();
  return 0;
};

void Parser::AddPointInArray() noexcept {
  all_vertices_.push_back(vertex_points_);
  all_textures_.push_back(texture_points_);
  all_normals_.push_back(normal_points_);
};

void Parser::DataClear() noexcept {
  vertex_points_.clear();
  texture_points_.clear();
  normal_points_.clear();
  delete faces_pars_;
};

void Parser::DebugPrint() noexcept {
  // std::cout << "V: ";
  // for (const auto &item : vertex_faces_) {
  //   for (const auto it : item) {
  //     std::cout << it << " ";
  //   }
  // }
  // std::cout << std::endl;

  // std::cout << "T: ";
  // for (const auto &item : texture_faces_) {
  //   for (const auto it : item) {
  //     std::cout << it << " ";
  //   }
  // }
  // std::cout << std::endl;

  std::cout << "N: ";
  for (const auto &item : normal_faces_) {
    for (const auto it : item) {
      std::cout << it << " ";
    }
  }
  std::cout << std::endl;
  // for (const auto item : all_vertices_) {
  //   std::cout << std::endl << "Model verices :";
  //   for (size_t i = 0; i < item.size(); ++i) {
  //     if (i % 4 == 0)
  //       std::cout << std::endl;
  //     std::cout << item[i] << " ||| ";
  //   }
  //   std::cout << std::endl;
  // }

  // for (const auto item : all_textures_) {
  //   std::cout << std::endl << "Model textures :";
  //   for (size_t i = 0; i < item.size(); ++i) {
  //     if (i % 3 == 0)
  //       std::cout << std::endl;
  //     std::cout << item[i] << " <|> ";
  //   }
  //   std::cout << std::endl;
  // }

  // for (const auto item : all_normals_) {
  //   std::cout << std::endl << "Model normals :";
  //   for (size_t i = 0; i < item.size(); ++i) {
  //     if (i % 3 == 0)
  //       std::cout << std::endl;
  //     std::cout << item[i] << " >|< ";
  //   }
  //   std::cout << std::endl;
  // }
};

void Parser::AddPoint(std::istringstream &data) noexcept {
  PointCoordinates vertex;
  data >> vertex.x;
  data >> vertex.y;
  data >> vertex.z;
  data >> vertex.a;
  StructFill(vertex);
};

void Parser::AddTexturePoint(std::istringstream &data) noexcept {
  TexturesCoordinates textures;
  data >> textures.u;
  data >> textures.v;
  data >> textures.w;
  StructFill(textures);
};

void Parser::AddNormalsPoint(std::istringstream &data) noexcept {
  NormalsCoordinate normals;
  data >> normals.x;
  data >> normals.y;
  data >> normals.z;
  StructFill(normals);
};

void Parser::SetStrategy(std::ifstream *file, int current_position) noexcept {
  if (texture_points_.empty() && normal_points_.empty()) { // v
    faces_pars_ = new VertexStrategy(file, current_position);
  } else if (!texture_points_.empty() && normal_points_.empty()) { // v/vt
    faces_pars_ = new VertexTexturesStrategy(file, current_position);
  } else if (texture_points_.empty() && !normal_points_.empty()) { // v//vn
    faces_pars_ = new VertexNormalsStrategy(file, current_position);
  } else {
    faces_pars_ = new VertexTexturesNormalsStrategy(file, current_position);
  }
};

void Parser::StructFill(const PointCoordinates &vertices_struct) noexcept {
  vertex_points_.push_back(vertices_struct.x);
  vertex_points_.push_back(vertices_struct.y);
  vertex_points_.push_back(vertices_struct.z);
  vertex_points_.push_back(vertices_struct.a);
};

void Parser::StructFill(const TexturesCoordinates &textures_struct) noexcept {
  texture_points_.push_back(textures_struct.u);
  texture_points_.push_back(textures_struct.v);
  texture_points_.push_back(textures_struct.w);
};

void Parser::StructFill(const NormalsCoordinate &normals_struct) noexcept {
  normal_points_.push_back(normals_struct.x);
  normal_points_.push_back(normals_struct.y);
  normal_points_.push_back(normals_struct.z);
};

void Parser::GetIndexes() noexcept {
  vertex_faces_.push_back(faces_pars_->GetVertices());
  texture_faces_.push_back(faces_pars_->GetTextures());
  normal_faces_.push_back(faces_pars_->GetNormals());
};

void Parser::Packer() noexcept {
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLint>>>
      vertices{all_vertices_, vertex_faces_};
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLint>>>
      normals{all_normals_, normal_faces_};
  CoordinatePacker *packer = new VertexNormalsCoordinatePacker(vertices, normals);
  coordinates_ = packer->GetCoordinates();
  delete packer;
}

} // namespace s21

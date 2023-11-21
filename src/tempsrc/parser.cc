#include "parser.h"

namespace s21 {
Parser::Parser(const std::string &filename) { ReadObj(filename); }

/* Private functions */
int Parser::ReadObj(const std::string &filename) {
  std::ifstream file;
  file.open(filename, std::ios::in);
  std::string line;
  if (!file) {
    return BAD_FILENAME;
  } else {
    while (std::getline(file, line)) {
      std::string prefix = line.substr(0, 2);
      std::istringstream data(line.substr(2));
      std::cout << line;
      if (prefix == "v ") {
        AddPoint(data);
      } else if (prefix == "vt") {
        AddTexturePoint(data);
      } else if (prefix == "vn") {
        AddNormalsPoint(data);
      } else if (prefix == "f ") {
        // std::istringstream data(line.substr(2));
        // std::string group;
        // while (data >> group) {
        //   /* std::vector<f_element> element; */
        //   std::istringstream data_group(group);
        //   char temp;
        //   /* int i_temp; */
        //   data_group >> e_temp.v_ >> temp >> e_temp.vt_ >> temp >>
        //   e_temp.vn_; std::cout << "origin " << group << std::endl; std::cout
        //   << "ho ho " << e_temp.v_ << " " << e_temp.vt_ << " "
        //             << e_temp.vn_ << std::endl;
      }
    }
  }
  return 0;
};

void Parser::AddPoint(std::istringstream &data) noexcept {
  PointCoordinates vertex;
  data >> vertex.x;
  data >> vertex.y;
  data >> vertex.z;
  data >> vertex.a;
  vertices_.push_back(vertex);
};

void Parser::AddTexturePoint(std::istringstream &data) noexcept {
  TexturesCoordinates textures;
  data >> textures.u;
  data >> textures.v;
  data >> textures.w;
  texture_points_.push_back(textures);
};

void Parser::AddNormalsPoint(std::istringstream &data) noexcept {
  NormalsCoordinate normals;
  data >> normals.x;
  data >> normals.y;
  data >> normals.z;
  normals_points_.push_back(normals);
};

} // namespace s21

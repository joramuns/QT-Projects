#include "object_model.h"

namespace s21 {

ObjectModel::ObjectModel(const std::string &filename) : filename_(filename) {
  Parser core_pars(filename_);
  all_vertices_ = core_pars.GetCoordinates();
  PrintResult();
  // all_textures_ = core_pars.GetTextures();
  // all_normals_ = core_pars.GetNormals();

  // vertex_indexes_ = core_pars.GetVertexIndexes();
  // texture_indexes_ = core_pars.GetTextureIndexes();
  // normal_indexes_ = core_pars.GetNormalIndexes();
};

ObjectModel::~ObjectModel(){};

void ObjectModel::PrintResult() const noexcept {
  std::cout << "Model: " << filename_ << std::endl << "Vertices:" << std::endl;
  int count = 0;
  for (const auto &item : all_vertices_) {
    for (const GLfloat &it : item) {
      if (count % 7 == 0) {
        std::cout << std::endl;
        count = 0;
      }
      std::cout << it << ' ';
      ++count;
    }
  }
  // count = 0;
  // std::cout << std::endl << "Vertex indexes: " << std::endl;
  // for (const auto &item : vertex_indexes_) {
  //   for (const auto &it : item) {
  //     if (count % 3 == 0) {
  //       std::cout << std::endl;
  //       count = 0;
  //     }
  //     std::cout << it << ' ';
  //     ++count;
  //   }
  // }
  // count = 0;
  // std::cout << std::endl << "Textures: " << std::endl;
  // for (const auto &item : all_textures_) {
  //   for (const auto &it : item) {
  //     if (count % 3 == 0) {
  //       std::cout << std::endl;
  //       count = 0;
  //     }
  //     std::cout << it << ' ';
  //     ++count;
  //   }
  // }
  // count = 0;
  // std::cout << std::endl << "Texture indexes: " << std::endl;
  // for (const auto &item : texture_indexes_) {
  //   for (const auto &it : item) {
  //     if (count % 3 == 0) {
  //       std::cout << std::endl;
  //       count = 0;
  //     }
  //     std::cout << it << ' ';
  //     ++count;
  //   }
  // }
  // count = 0;
  // std::cout << std::endl << "Normals: " << std::endl;
  // for (const auto &item : all_normals_) {
  //   for (const auto &it : item) {
  //     if (count % 3 == 0) {
  //       std::cout << std::endl;
  //       count = 0;
  //     }
  //     std::cout << it << ' ';
  //     ++count;
  //   }
  // }
  // count = 0;
  // std::cout << std::endl << "Normals indexes: " << std::endl;
  // for (const auto &item : normal_indexes_) {
  //   for (const auto &it : item) {
  //     if (count % 3 == 0) {
  //       std::cout << std::endl;
  //       count = 0;
  //     }
  //     std::cout << it << ' ';
  //     ++count;
  //   }
  // }
  // std::cout << std::endl;
}

std::vector<std::vector<GLfloat>> ObjectModel::GetVertices() const noexcept {
  return all_vertices_;
};

std::vector<std::vector<GLfloat>> ObjectModel::GetTextures() const noexcept {
  return all_textures_;
};

std::vector<std::vector<GLfloat>> ObjectModel::GetNormals() const noexcept {
  return all_normals_;
};

std::vector<std::vector<GLuint>>
ObjectModel::GetVertexIndexes() const noexcept {
  return vertex_indexes_;
};

std::vector<std::vector<GLuint>>
ObjectModel::GetTextureIndexes() const noexcept {
  return texture_indexes_;
};

std::vector<std::vector<GLuint>>
ObjectModel::GetNormalIndexes() const noexcept {
  return normal_indexes_;
};
} // namespace s21
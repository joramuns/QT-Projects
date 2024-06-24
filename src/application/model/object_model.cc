#include "object_model.h"

namespace s21 {

ObjectModel::ObjectModel(const std::string &filename) : filename_(filename) {
  Parser core_pars(filename_);
  all_vertices_ = core_pars.GetCoordinates();
  stride_ = core_pars.GetStride();
  model_info_.vertices = core_pars.GetVertNumber();
  model_info_.edges = core_pars.GetEdgeNumber();
};

ObjectModel::~ObjectModel(){};

void ObjectModel::PrintResult() const noexcept {
  /* std::cout << "Model: " << filename_ << std::endl << "Vertices:" << std::endl; */
  /* int count = 0; */
  /* for (const auto &item : all_vertices_) { */
  /*   for (const GLfloat &it : item) { */
  /*     if (count % 7 == 0) { */
  /*       std::cout << std::endl; */
  /*     } */
  /*     std::cout << it << ' '; */
  /*     ++count; */
  /*   } */
  /* } */
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

int ObjectModel::GetStride() const noexcept { return stride_; }

std::vector<std::vector<GLuint>> ObjectModel::GetVertexIndexes()
    const noexcept {
  return vertex_indexes_;
};

std::vector<std::vector<GLuint>> ObjectModel::GetTextureIndexes()
    const noexcept {
  return texture_indexes_;
};

std::vector<std::vector<GLuint>> ObjectModel::GetNormalIndexes()
    const noexcept {
  return normal_indexes_;
};
}  // namespace s21

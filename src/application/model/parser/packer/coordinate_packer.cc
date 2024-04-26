#include "coordinate_packer.h"

#include <iostream>
namespace s21 {
CoordinatePacker::CoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &vertices) noexcept
    : vertices_(vertices) {}

std::vector<std::vector<GLfloat>> CoordinatePacker::GetCoordinates()
    const noexcept {
  return all_coordinates_;
};

bool CoordinatePacker::CheckRange(const std::vector<GLfloat> &vec,
                                  const GLint &index) const noexcept {
  std::cout << vec.size() << " - size " << index << " - index" << std::endl;
  return (index < static_cast<GLint>(vec.size()));
}

VertexCoordinatePacker::VertexCoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &vertices) noexcept
: CoordinatePacker(vertices){
  Pack();
};

void VertexCoordinatePacker::Pack() noexcept {
  for (size_t i = 0; i < vertices_.second.size(); ++i) {
    std::vector<GLfloat> tmp;
    for (size_t j = 0; j < vertices_.second[i].size(); ++j) {
      GLint index_vertices = vertices_.second[i][j];
      for (size_t k = 0; k < 4; ++k) {
        if (index_vertices < 0) {
          index_vertices = (vertices_.first[i].size() / 4) + (++index_vertices);
        }
        if (CheckRange(vertices_.first[i], index_vertices * 4 + k)) {
          tmp.push_back(vertices_.first[i][index_vertices * 4 + k]);
        } else {
          is_pack_ = false;
        }
      }
    }
    all_coordinates_.push_back(tmp);
  }
  if (!is_pack_) {
    all_coordinates_.clear();
  }
};

VertexTexturesCoordinatePacker::VertexTexturesCoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &vertices,
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &textures) noexcept
    : CoordinatePacker(vertices) {
  textures_ = textures;
  Pack();
};

void VertexTexturesCoordinatePacker::Pack() noexcept {
  for (size_t i = 0; i < vertices_.second.size(); ++i) {
    std::vector<GLfloat> tmp;
    for (size_t j = 0; j < vertices_.second[i].size(); ++j) {
      GLint index_vertices = vertices_.second[i][j];
      for (size_t k = 0; k < 4; ++k) {
        if (index_vertices < 0) {
          index_vertices = (vertices_.first[i].size() / 4) + (++index_vertices);
        }
        if (CheckRange(vertices_.first[i], index_vertices * 4 + k)) {
          tmp.push_back(vertices_.first[i][index_vertices * 4 + k]);
        } else {
          is_pack_ = false;
        }
      }
      GLint index_textures = textures_.second[i][j];
      for (size_t k = 0; k < 2; ++k) {
        if (index_textures < 0) {
          index_textures = (textures_.first[i].size() / 2) + (++index_textures);
        }
        if (CheckRange(textures_.first[i], index_textures * 2 + k)) {
          tmp.push_back(textures_.first[i][index_textures * 2 + k]);
        } else {
          is_pack_ = false;
        }
      }
    }
    all_coordinates_.push_back(tmp);
  }
  if (!is_pack_) {
    all_coordinates_.clear();
  }
};

VertexNormalsCoordinatePacker::VertexNormalsCoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &vertices,
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &normals) noexcept
    : CoordinatePacker(vertices) {
  normals_ = normals;
  Pack();
};

void VertexNormalsCoordinatePacker::Pack() noexcept {
  for (size_t i = 0; i < vertices_.first.size(); ++i) {
    std::vector<GLfloat> tmp;
    for (size_t j = 0; j < vertices_.second[i].size(); ++j) {
      GLint index_vertices = vertices_.second[i][j];
      for (size_t k = 0; k < 4; ++k) {
        if (index_vertices < 0) {
          index_vertices = (vertices_.first[i].size() / 4) + (++index_vertices);
        }
        if (CheckRange(vertices_.first[i], index_vertices * 4 + k)) {
          tmp.push_back(vertices_.first[i][index_vertices * 4 + k]);
        } else {
          is_pack_ = false;
        }
      }
      GLint index_normals = normals_.second[i][j];
      for (size_t k = 0; k < 3; ++k) {
        if (index_normals < 0) {
          index_normals = (normals_.first[i].size() / 3) + (++index_normals);
        }
        if (CheckRange(normals_.first[i], index_normals * 3 + k)) {
          GLfloat norm_coordinate = normals_.first[i][index_normals * 3 + k];
          if (norm_coordinate < 0) norm_coordinate *= -1;
          tmp.push_back(norm_coordinate);
        } else {
          is_pack_ = false;
        }
      }
    }
    all_coordinates_.push_back(tmp);
  }
  // if (!is_pack_) {
  //   all_coordinates_.clear();
  // }
};

VertexTexturesNormalsCoordinatePacker::VertexTexturesNormalsCoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &vertices,
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &textures,
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &normals) noexcept
    : CoordinatePacker(vertices) {
  textures_ = textures;
  normals_ = normals;
  Pack();
};

void VertexTexturesNormalsCoordinatePacker::Pack() noexcept {
  for (size_t i = 0; i < vertices_.second.size(); ++i) {
    std::vector<GLfloat> tmp;
    for (size_t j = 0; j < vertices_.second[i].size(); ++j) {
      GLint index_vertices = vertices_.second[i][j];
      for (size_t k = 0; k < 4; ++k) {
        if (index_vertices < 0) {
          index_vertices = (vertices_.first[i].size() / 4) + (++index_vertices);
        }
        if (CheckRange(vertices_.first[i], index_vertices * 4 + k)) {
          tmp.push_back(vertices_.first[i][index_vertices * 4 + k]);
        } else {
          is_pack_ = false;
        }
      }
      GLint index_textures = textures_.second[i][j];
      for (size_t k = 0; k < 2; ++k) {
        if (index_textures < 0) {
          index_textures = (normals_.first[i].size() / 2) + (++index_textures);
        }
        if (CheckRange(textures_.first[i], index_textures * 2 + k)) {
          tmp.push_back(textures_.first[i][index_textures * 2 + k]);
        } else {
          is_pack_ = false;
        }
      }
      GLint index_normals = normals_.second[i][j];
      for (size_t k = 0; k < 3; ++k) {
        if (index_normals < 0) {
          index_normals = (normals_.first[i].size() / 3) + (++index_normals);
        }
        if (CheckRange(normals_.first[i], index_normals * 3 + k)) {
          GLfloat norm_coordinate = normals_.first[i][index_normals * 3 + k];
          if (norm_coordinate < 0) norm_coordinate *= -1;
          tmp.push_back(norm_coordinate);
        } else {
          std::cout << "zalet" << std::endl;
          is_pack_ = false;
        }
      }
    }
    all_coordinates_.push_back(tmp);
  }
  if (!is_pack_) {
    all_coordinates_.clear();
  }
};

}  // namespace s21

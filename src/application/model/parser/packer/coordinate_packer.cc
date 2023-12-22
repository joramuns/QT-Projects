#include "coordinate_packer.h"
#include <iostream>
namespace s21 {
CoordinatePacker::CoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &vertices) noexcept
    : vertices_(vertices) {}

std::vector<std::vector<GLfloat>>
CoordinatePacker::GetCoordinates() const noexcept {
  return all_coordinates_;
};

VertexCoordinatePacker::VertexCoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLint>>> &vertices) noexcept
    : CoordinatePacker(vertices) {
  Pack();
};

void VertexCoordinatePacker::Pack() noexcept {
  for (size_t i = 0; i < vertices_.second.size(); ++i) {
    std::vector<GLfloat> tmp;
    for (size_t j = 0; j < vertices_.second[i].size(); ++j) {
      for (size_t k = 0; k < 4; ++k) {
        tmp.push_back(vertices_.first[i][vertices_.second[i][j] * 4 + k]);
      }
    }
    all_coordinates_.push_back(tmp);
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
      for (size_t k = 0; k < 4; ++k) {
        tmp.push_back(vertices_.first[i][vertices_.second[i][j] * 4 + k]);
      }
      for (size_t k = 0; k < 3; ++k) {
        tmp.push_back(textures_.first[i][textures_.second[i][j] * 3 + k]);
      }
    }
    all_coordinates_.push_back(tmp);
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
      for (size_t k = 0; k < 4; ++k) {
        GLint index = vertices_.second[i][j];
        std::cout << index << std::endl;
        // std::cout << index << std::endl;
        // if (index < 0) {
        //   index = vertices_.first[i].size() + index;
        // }
        tmp.push_back(vertices_.first[i][index * 4 + k]);
      }
      for (size_t k = 0; k < 3; ++k) {
        GLint index = normals_.second[i][j];
        // if (index < 0) {
        //   index = normals_.first[i].size() + index;
        // }
        GLfloat norm_coordinate = normals_.first[i][index * 3 + k];
        if (norm_coordinate < 0) norm_coordinate *= -1;
        tmp.push_back(norm_coordinate);
      }
    }
    all_coordinates_.push_back(tmp);
  }
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
      for (size_t k = 0; k < 4; ++k) {
        tmp.push_back(vertices_.first[i][vertices_.second[i][j] * 4 + k]);
      }
      for (size_t k = 0; k < 3; ++k) {
        tmp.push_back(textures_.first[i][textures_.second[i][j] * 3 + k]);
      }
      for (size_t k = 0; k < 3; ++k) {
        GLfloat norm_coordinate = normals_.first[i][normals_.second[i][j] * 3 + k];
        if (norm_coordinate < 0) norm_coordinate *= -1;
        tmp.push_back(norm_coordinate);
      }
    }
    all_coordinates_.push_back(tmp);
  }
};

} // namespace s21
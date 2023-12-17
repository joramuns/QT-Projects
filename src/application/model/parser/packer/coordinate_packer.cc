#include "coordinate_packer.h"

namespace s21 {
CoordinatePacker::CoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLuint>>> &vertices) noexcept
    : vertices_(vertices) {}

std::vector<std::vector<GLfloat>>
CoordinatePacker::GetCoordinates() const noexcept {
  return all_coordinates_;
};

VertexCoordinatePacker::VertexCoordinatePacker(
    const std::pair<std::vector<std::vector<GLfloat>>,
                    std::vector<std::vector<GLuint>>> &vertices) noexcept
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

// VertexTexturesCoordinatePacker::VertexTexturesCoordinatePacker(
//     const std::vector<std::vector<GLfloat>> &vertices,
//     const std::vector<std::vector<GLfloat>> &textures) noexcept
//     : CoordinatePacker(vertices) {
//   textures_coordinates_ = textures;
// };

// void VertexTexturesCoordinatePacker::Pack() noexcept {
//   for (size_t i = 0; i < vertices_coordinates_.size(); ++i) {
//     std::vector<GLfloat> tmp;
//     for (size_t j = 0; j < vertices_coordinates_[i].size(); ++j) {
//     }
//   }
// }
} // namespace s21
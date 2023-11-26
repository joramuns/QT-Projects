#include "coordinatecontain.h"

namespace s21 {
CoordinateContain::CoordinateContain(
    const std::vector<PointCoordinates> vp,
    const std::vector<TexturesCoordinates> tp,
    const std::vector<NormalsCoordinate> np) noexcept
    : vertex_points_(vp), texture_points_(tp), normal_points_(np){};

const PointCoordinates &
CoordinateContain::GetPointCoordinates(const int i) const noexcept {
  return vertex_points_[i];
}

const TexturesCoordinates &
CoordinateContain::GetTexturesCoordinates(const int i) const noexcept {
  return texture_points_[i];
}

const NormalsCoordinate &
CoordinateContain::GetNormalsCoordinates(const int i) const noexcept {
  return normal_points_[i];
}

} // namespace s21
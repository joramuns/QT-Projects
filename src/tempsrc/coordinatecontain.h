#ifndef COORDINATE_CONTAIN_H
#define COORDINATE_CONTAIN_H
// #include <GL/glut.h>
#include <OpenGL/gl.h>

#include <vector>

#include "coordinatestruct.h"

namespace s21 {
class CoordinateContain {
public:
  CoordinateContain() = delete;
  CoordinateContain(const std::vector<PointCoordinates> vp,
                    const std::vector<TexturesCoordinates> tp,
                    const std::vector<NormalsCoordinate> np) noexcept;

  const PointCoordinates &GetPointCoordinates(const int i) const noexcept;
  const TexturesCoordinates &GetTexturesCoordinates(const int i) const noexcept;
  const NormalsCoordinate &GetNormalsCoordinates(const int i) const noexcept;

private:
  const std::vector<PointCoordinates> vertex_points_;
  const std::vector<TexturesCoordinates> texture_points_;
  const std::vector<NormalsCoordinate> normal_points_;
};
} // namespace s21

#endif
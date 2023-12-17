#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_PACKER_COORDINATE_PACKER_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_PACKER_COORDINATE_PACKER_H

#include <OpenGL/gl.h>
#include <vector>

namespace s21 {
class CoordinatePacker {
public:
  CoordinatePacker() = delete;
  CoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLuint>>> &vertices) noexcept;
  virtual ~CoordinatePacker(){};

  std::vector<std::vector<GLfloat>> GetCoordinates() const noexcept;

protected:
  virtual void Pack() = 0;

protected:
  std::vector<std::vector<GLfloat>> all_coordinates_;

  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLuint>>>
      vertices_;
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLuint>>>
      textures_;
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLuint>>>
      normals_;
};

class VertexCoordinatePacker : public CoordinatePacker {
public:
  VertexCoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLuint>>> &vertices) noexcept;

private:
  void Pack() noexcept override;
};

class VertexTexturesCoordinatePacker : CoordinatePacker {
public:
  VertexTexturesCoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLuint>>> &vertices,
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLuint>>> &textures) noexcept;

private:
  void Pack() noexcept override;
};

class VertexTexturesNormalsCoordinatePacker : CoordinatePacker {
public:
  VertexTexturesNormalsCoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLuint>>> &vertices,
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLuint>>> &textures,
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLuint>>> &normals) noexcept;

private:
  void Pack() noexcept override;
};
} // namespace s21

#endif // CPP4_3DVIEWER_V2_MODEL_PARSER_PACKER_COORDINATE_PACKER_H
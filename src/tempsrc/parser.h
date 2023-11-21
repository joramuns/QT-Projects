#include <OpenGL/gl.h>
// #include <epoxy/gl.h>
// #include <glm/glm.hpp>
/* -I/Users/joramuns/.brew/Cellar/glm/0.9.9.8/include */
/* brew install glm */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define BAD_FILENAME 1

namespace s21 {
class Parser {
 public:
  Parser() = delete;
  explicit Parser(const std::string &filename);

 private:
  int ReadObj(const std::string &filename);

  struct PointCoordinates {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat a{0.0};
  };

  struct TexturesCoordinates {
    GLfloat u;
    GLfloat v;
    GLfloat w{0.0};
  };

  struct NormalsCoordinate {
    GLfloat x;
    GLfloat y;
    GLfloat z;
  };

  void AddPoint(std::istringstream &data) noexcept;
  void AddTexturePoint(std::istringstream &data) noexcept;
  void AddNormalsPoint(std::istringstream &data) noexcept;
  void ParsFaces() noexcept;

private:
  std::vector<PointCoordinates> vertex_points_;
  std::vector<TexturesCoordinates> texture_points_;
  std::vector<NormalsCoordinate> normal_points_;
  // std::vector<GLuint> faces_;
  std::vector<GLfloat> vertices_;
  std::vector<GLfloat> textures_;
  std::vector<GLfloat> normals_;
};
}  // namespace s21

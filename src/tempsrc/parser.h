#include <epoxy/gl.h>
/* #include <glm/glm.hpp> */
/* -I/Users/joramuns/.brew/Cellar/glm/0.9.9.8/include */
/* brew install glm */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

  // struct f_element {
  //   GLuint v_{0};
  //   GLuint vt_{0};
  //   GLuint vn_{0};
  // };
private:
  std::vector<PointCoordinates> vertices_;
  std::vector<TexturesCoordinates> textures_;
  std::vector<NormalsCoordinate> normals_;
  // std::vector<std::vector<f_element>> f_elements_;
  std::vector<GLuint> faces_;
};
}  // namespace s21

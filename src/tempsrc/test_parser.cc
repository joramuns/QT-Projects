#include "parser.h"

void wrong_filename() {
  s21::Parser test("cube.obj");
  std::cout << "Success" << std::endl;
}

void model_filename(const std::string &filename) {
  s21::Parser test(filename);
  std::cout << "Success" << std::endl;
}

int main() {
  std::cout << "test 1:" << std::endl;
  wrong_filename();
  std::cout << "test 2: Only Vertex obj" << std::endl;
  model_filename("../../data-samples/test_vertex.obj");
  std::cout << "test 3: Vertex Textures obj" << std::endl;
  model_filename("../../data-samples/test_vertex_textures.obj");
  std::cout << "test 3: Vertex Normals obj" << std::endl;
  model_filename("../../data-samples/test_vertex_normals.obj");
  std::cout << "test 3: Vertex Textures Normals obj" << std::endl;
  model_filename("../../data-samples/test_vertex_textures_normals.obj");
  return 0;
}

#include "parser.h"

void wrong_filename() {
  s21::Parser test("cube.obj");
  std::cout << "Success" << std::endl;
}

void model_pars(const std::string &filename) {
  s21::Parser test(filename);
  std::cout << "Success" << std::endl;
}

int main() {
  // std::cout << "test 1:" << std::endl;
  // wrong_filename();
  // std::cout << "test 2: Only Vertex obj" << std::endl;
  // model_pars("../../data-samples/test_vertex.obj");
  // std::cout << "test 3: Vertex Textures obj" << std::endl;
  // model_pars("../../data-samples/test_vertex_textures.obj");
  // std::cout << "test 4: Vertex Normals obj" << std::endl;
  // model_pars("../../data-samples/test_vertex_normals.obj");
  // std::cout << "test 5: Vertex Textures Normals obj" << std::endl;
  // model_pars("../../data-samples/test_vertex_textures_normals.obj");
  // std::cout << "test 6: Multiobject Vertex Model obj" << std::endl;
  // model_pars("../../data-samples/test_multiobject_vertex.obj");
  // std::cout << "test 7: Multiobject Vertex Textures Model obj" << std::endl;
  // model_pars("../../data-samples/test_multiobject_vertex_textures.obj");
  // std::cout << "test 8: Multiobject Vertex Normals Model obj" << std::endl;
  // model_pars("../../data-samples/test_multiobject_vertex_normals.obj");
  std::cout << "test 9: Multiobject Vertex Textures Normals Model obj" << std::endl;
  model_pars("../../data-samples/test_multiobject_vertex_textures_normals.obj");
  return 0;
}

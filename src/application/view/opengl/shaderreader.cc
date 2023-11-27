#include "shaderreader.h"

// TEMP
#include <iostream>

namespace s21 {
std::string ReadShader(const std::string &filename) {
  std::string shader;
  std::ifstream file(filename, std::ifstream::in);
  std::string keka = "keka\n";
  while (std::getline(file, shader)) {
    std::cout << keka << shader << std::endl;
  }

  /* shader = std::string(std::istreambuf_iterator<char>(file), */
                       /* std::istreambuf_iterator<char>()); */

  /* std::cout << "here " << shader << std::endl; */

  return shader;
}
}  // namespace s21

#include "shaderreader.h"

// TEMP
#include <iostream>

namespace s21 {
std::string ReadShader(const std::string &filename) {
  std::string shader;
  std::ifstream file(filename);
  std::string keka = "keka\n";

  shader = std::string(std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>());

  return shader;
}
}  // namespace s21

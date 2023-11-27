#ifndef VIEW_OPENGL_SHADERREADER_H_
#define VIEW_OPENGL_SHADERREADER_H_

#include <fstream>
#include <sstream>
#include <string>

namespace s21 {
std::string ReadShader(const std::string &filename);
}  // namespace s21
#endif  // VIEW_OPENGL_SHADERREADER_H_

#include "new-parser.h"

namespace s21 {

NewParser::NewParser(const std::string &filename) {
  if (!IsCorrectFileFormat(filename)) {
    throw std::invalid_argument("\n Invalid file format");
  } else if (!IsFileExist(filename)) {
    throw std::invalid_argument("\n File does not exist");
  } else {
  }
}

bool NewParser::IsCorrectFileFormat(
    const std::string &filename) const noexcept {
  return (filename.substr(filename.length() - 3, 3) == "obj");
}

bool NewParser::IsFileExist(const std::string &filename) const noexcept {
  bool result = true;
  std::ifstream file;
  file.open(filename, std::ios::in);
  if (!file) {
    result = false;
  } else {
    file.close();
  }
  return result;
}

void NewParser::DataRead(const std::string &filename) const noexcept {
  std::ifstream file;
  file.open(filename, std::ios::in);
  std::string line;
  int file_position;
  while (std::getline(file, line)) {
    
  }
}
} // namespace s21
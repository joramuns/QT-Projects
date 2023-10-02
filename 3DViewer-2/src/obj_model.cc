#include "obj_model.h"

namespace s21 {
ObjModel::ObjModel() {}
ObjModel::ObjModel(const std::string &filename) { ReadObj(); }

/* Private functions */
int ObjModel::ReadObj() {
  std::ifstream file;
  file.open("cube.obj", std::ios::in);
  if (!file) {
    std::cout << "File error" << std::endl;
  } else {
    std::string line;
    while (std::getline(file, line)) {
      std::string prefix = line.substr(0, 2);
      if (prefix == "v ") {
        std::istringstream data(line.substr(2));
        point vertex;
        data >> vertex.x_;
        data >> vertex.y_;
        data >> vertex.z_;
      } else if (prefix == "f ") {
          
      }
    }
  }

  file.close();
  return 0;
}

}  // namespace s21

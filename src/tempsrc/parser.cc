#include "parser.h"

namespace s21 {
Parser::Parser(const std::string &filename) { ReadObj(filename); }

/* Private functions */
int Parser::ReadObj(const std::string &filename) {
  std::ifstream file;
  try {
    file.open(filename, std::ios::in);
    /* file.exceptions(std::ifstream::failbit); */
    std::cout << "here" << std::endl;
    std::string line;
    if (file) {
    } else {
      std::cout << "opana" << std::endl;
    }
    while (std::getline(file, line)) {
      std::string prefix = line.substr(0, 2);
      if (prefix == "v ") {
        std::istringstream data(line.substr(2));
        point vertex;
        data >> vertex.x_;
        data >> vertex.y_;
        data >> vertex.z_;
        data >> vertex.a_;
        std::cout << vertex.x_ << " " << vertex.y_ << " " << vertex.z_ << " "
                  << vertex.a_ << std::endl;
      } else if (prefix == "f ") {
        std::istringstream data(line.substr(2));
        std::string group;
        while (data >> group) {
          /* std::vector<f_element> element; */
          std::istringstream data_group(group);
          f_element e_temp;
          char temp;
          /* int i_temp; */
          data_group >> e_temp.v_ >> temp >> e_temp.vt_ >> temp >> e_temp.vn_;
          std::cout << "origin " << group << std::endl;
          std::cout << "ho ho " << e_temp.v_ << " " << e_temp.vt_ << " " << e_temp.vn_ << std::endl;

        }
      }
    }
  } catch (const std::ifstream::failure &e) {
    std::cout << "Wrong filename" << std::endl;
  }
  return 0;
}

}  // namespace s21

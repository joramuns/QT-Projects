#ifndef CPP4_3DVIEWER_V2_MODEL_FASADE_FASADE_H
#define CPP4_3DVIEWER_V2_MODEL_FASADE_FASADE_H
#include <vector>

#include "../parser/parser.h"
#include "../object_model.h"


namespace s21 {
class Fasade {
public:
  void AddModel(const std::string &filename) noexcept;
  
  //debug
  void PrintDate() const noexcept;
private:
  std::vector<ObjectModel> models_;
};
} // namespace s21

#endif // CPP4_3DVIEWER_V2_MODEL_FASADE_FASADE_H
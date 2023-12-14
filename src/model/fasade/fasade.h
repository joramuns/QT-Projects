#ifndef CPP4_3DVIEWER_V2_MODEL_FASADE_FASADE_H
#define CPP4_3DVIEWER_V2_MODEL_FASADE_FASADE_H
#include <vector>

#include "../parser/parser.h"
#include "../object_model.h"


namespace s21 {
class Fasade {
public:
  ObjectModel AddModel(const std::string &filename) noexcept;
  void RemoveModel(int model_number) noexcept;
  ObjectModel GetModel(const unsigned int index) const noexcept;
  std::size_t CountModel() const noexcept;
  //debug
  void PrintDate() const noexcept;
private:
  std::vector<ObjectModel> models_;
};
} // namespace s21

#endif // CPP4_3DVIEWER_V2_MODEL_FASADE_FASADE_H

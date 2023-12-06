#include "fasade.h"

namespace s21 {
void Fasade::AddModel(const std::string &filename) noexcept {
  ObjectModel model(filename);
  models_.push_back(model);
};

void Fasade::PrintDate() const noexcept {
  for (const ObjectModel item : models_) {
    item.PrintResult();
  }
}
}
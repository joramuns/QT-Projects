#include "fasade.h"

namespace s21 {
ObjectModel Fasade::AddModel(const std::string &filename) noexcept {
  ObjectModel model(filename);
  models_.push_back(model);

  return model;
};

void Fasade::PrintDate() const noexcept {
  for (const ObjectModel &item : models_) {
    item.PrintResult();
  }
};

ObjectModel Fasade::GetModel(const unsigned int index) const noexcept {
  return models_[index];
};
}

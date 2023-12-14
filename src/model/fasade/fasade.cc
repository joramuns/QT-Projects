#include "fasade.h"

namespace s21 {
ObjectModel Fasade::AddModel(const std::string &filename) noexcept {
  ObjectModel model(filename);
  models_.push_back(model);

  return model;
};

void Fasade::RemoveModel(int model_number) noexcept {
  models_.erase(models_.begin() + model_number);
}

std::size_t Fasade::CountModel() const noexcept { return models_.size(); }

void Fasade::PrintDate() const noexcept {
  for (const ObjectModel &item : models_) {
    item.PrintResult();
  }
};

ObjectModel Fasade::GetModel(const unsigned int index) const noexcept {
  return models_[index];
};
}  // namespace s21

#include "facade.h"

namespace s21 {
Facade::Facade() : context_(new GLWidget){};

Facade::~Facade() { std::cout << "facade context: " << context_ << std::endl; }

void Facade::AddModel(const std::string &filename) noexcept {
  ObjectModel model(filename);
  models_.push_back(model);

  std::vector<GLfloat> vertices;
  for (const auto &item : model.GetVertices()) {
    vertices.insert(vertices.end(), item.begin(), item.end());
  }
  context_->LoadModel(vertices);
};

void Facade::RemoveModel(int model_number) noexcept {
  models_.erase(models_.begin() + model_number);
  context_->UnloadModel(model_number);
}

std::size_t Facade::CountModel() const noexcept { return models_.size(); }

void Facade::PrintDate() const noexcept {
  for (const ObjectModel &item : models_) {
    item.PrintResult();
  }
};

ObjectModel Facade::GetModel(const unsigned int index) const noexcept {
  return models_[index];
};

GLWidget *Facade::GetContext() const noexcept { return context_; }

void Facade::Rotate(double value, char axis, int model_number) {
  context_->Rotate(value, axis, model_number);
  context_->update();
}

void Facade::Move(double value, char axis, int model_number) {
  context_->Move(value, axis, model_number);
  context_->update();
}

void Facade::Scale(double value, int model_number) {
  context_->Scale(value, model_number);
  context_->update();
}

void Facade::SwitchProjection(int index) {
  context_->SwitchProjection(index);
  context_->update();
}

void Facade::SwitchWireframe(int index) {
  context_->SwitchWireframe(index);
  context_->update();
}

void Facade::ChangeSceneColor(QColor scene_color) {
  context_->SetSceneColor(scene_color);
}

void Facade::ChangeVertexColor(QVector3D vertex_color) {
  context_->SetVertexColor(vertex_color);
}

void Facade::ChangeEdgeColor(QVector3D edge_color) {
  context_->SetEdgeColor(edge_color);
}

void Facade::ChangeVertexOption(int index) {
  context_->SetVertexOption(index);
  context_->update();
}

void Facade::ChangeEdgeOption(int index) {
  context_->SetEdgeOption(index);
  context_->update();
}

void Facade::ChangeVertexSize(double value) {
  context_->SetVertexSize(value);
  context_->update();
}

void Facade::ChangeEdgeSize(double value) {
  context_->SetEdgeSize(value);
  context_->update();
}
}  // namespace s21

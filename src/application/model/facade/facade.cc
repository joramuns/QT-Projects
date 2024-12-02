#include "facade.h"

namespace s21 {
Facade::Facade() : context_(new GLWidget){};

Facade::~Facade() {}

std::string Facade::AddModel(const std::string &filename) noexcept {
  objl::Loader loader;
  loader.LoadFile(filename);
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  unsigned vert_number = 0;
  unsigned edge_number = 0;

  for (const auto &mesh : loader.LoadedMeshes) {
    for (const auto &item : mesh.Indices) {
      auto vi = mesh.Vertices[item];
      Vertex v;
      v.position = QVector3D(vi.Position.X, vi.Position.Y, vi.Position.Z);
      v.normal = QVector3D(vi.Normal.X, vi.Normal.Y, vi.Normal.Z);
      v.texCoord = QVector2D(vi.TextureCoordinate.X, vi.TextureCoordinate.Y);
      vertices.push_back(v);
    }
    vert_number += mesh.Vertices.size();
    edge_number += mesh.Indices.size();
  }
  context_->LoadModel2(vertices);
  ++models_;

  std::string model_name = filename.substr(filename.rfind("/") + 1) +
                           ", vertices: " + std::to_string(vert_number) +
                           ", edges: " + std::to_string(edge_number);
  return model_name;
};

void Facade::RemoveModel(int model_number) noexcept {
  --models_;
  context_->UnloadModel2(model_number);
  /* context_->UnloadModel(model_number); */
}

void Facade::PrintDate() const noexcept {
    /* for (const ObjectModel &item : models_) { */
    /*   item.PrintResult(); */
    /* } */
};

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

void Facade::ChangeLightColor(const QVector3D &value) {
  context_->SetLightColor(value);
  context_->update();
}

void Facade::ChangeLightPosition(const QVector3D &value) {
  context_->SetLightPosition(value);
  context_->update();
}

void Facade::TakeScreenshot(const QString &filename) {
  context_->SaveScreenshot(filename);
}

void Facade::TakeGif(const QString &filename) { context_->SaveGif(filename); }

}  // namespace s21

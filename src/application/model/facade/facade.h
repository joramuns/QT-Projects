#ifndef CPP4_3DVIEWER_V2_MODEL_FACADE_FACADE_H
#define CPP4_3DVIEWER_V2_MODEL_FACADE_FACADE_H
#include <vector>

#include "../parser/parser.h"
#include "../object_model.h"
#include "../context/glwidget.h"


namespace s21 {
class Facade {
public:
  Facade();

  void AddModel(const std::string &filename) noexcept;
  void RemoveModel(int model_number) noexcept;
  ObjectModel GetModel(const unsigned int index) const noexcept;
  std::size_t CountModel() const noexcept;
  GLWidget *GetContext() const noexcept;
  //debug
  void PrintDate() const noexcept;

  void Rotate(double value, char axis, int model_number);
  void Move(double value, char axis, int model_number);
  void Scale(double value, int model_number);
  void SwitchProjection(int index);
  void SwitchWireframe(int index);
  void ChangeSceneColor(QColor scene_color);
  void ChangeVertexColor(QVector3D vertex_color);
  void ChangeEdgeColor(QVector3D edge_color);
  void ChangeVertexOption(int index);
  void ChangeEdgeOption(int index);
  void ChangeVertexSize(double value);
  void ChangeEdgeSize(double value);

private:
  std::vector<ObjectModel> models_;
  GLWidget *context_;
};
} // namespace s21

#endif // CPP4_3DVIEWER_V2_MODEL_FACADE_FACADE_H

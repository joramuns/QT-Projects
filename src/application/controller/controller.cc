#include "controller.h"

// TEMP
#include <iostream>
#include <vector>

namespace s21 {
Controller::Controller(View *v, Fasade *f) : view_(v), fasade_(f) {
  connect(view_, &View::ViewTransformSignal, this,
          &Controller::ControllerTransformSlot);

  connect(view_, &View::OpenFileSignal, this,
          &Controller::ControllerOpenFileSlot);

  connect(view_, &View::CloseFileSignal, this,
          &Controller::ControllerCloseFileSlot);

  connect(view_, &View::SceneOptionSignal, this,
          &Controller::ControllerSceneOptionSlot);

  connect(view_, &View::ExtraSceneOptionSignal, this,
          &Controller::ControllerExtraSceneOptionSlot);

  connect(view_, &View::SceneColorSignal, this,
          &Controller::ControllerSceneColor);

  connect(view_, &View::VertexColorSignal, this,
          &Controller::ControllerVertexColor);

  connect(view_, &View::EdgeColorSignal, this,
          &Controller::ControllerEdgeColor);
}

void Controller::ControllerTransformSlot(double value, char axis, int type,
                                         int model_number) {
  std::cout << (type ? axis == 'S' ? "Scale " : "Move " : "Rotate ")
            << "tab: " << axis << " " << value << " " << std::endl;
  if (fasade_->CountModel() && model_number >= 0) {
    if (type == ROTATE) {
      view_->Rotate(value, axis, model_number);
    } else if (type == MOVE) {
      view_->Move(value, axis, model_number);
    } else if (type == SCALE) {
      view_->Scale(value, model_number);
    }
  }
}

void Controller::ControllerOpenFileSlot(QString filename) {
  std::cout << "Open file " << filename.toStdString() << std::endl;
  ObjectModel a = fasade_->AddModel(filename.toStdString());
  std::vector<GLfloat> vertices;
  for (const auto &item : a.GetVertices()) {
    vertices.insert(vertices.end(), item.begin(), item.end());
  }
  view_->LoadModel(vertices);
  view_->AddListWidgetItem(filename);
}

void Controller::ControllerCloseFileSlot(int model_number) {
  if (fasade_->CountModel()) {
    fasade_->RemoveModel(model_number);
    view_->UnloadModel(model_number);
  }
}

void Controller::ControllerSceneOptionSlot(int index) {
  view_->SwitchProjection(index);
}

void Controller::ControllerExtraSceneOptionSlot(int index) {
  view_->SwitchWireframe(index);
}

void Controller::ControllerSceneColor(QColor scene_color) {
  view_->ChangeSceneColor(scene_color);
}

void Controller::ControllerVertexColor(QVector3D vertex_color) {
  view_->ChangeVertexColor(vertex_color);
}

void Controller::ControllerEdgeColor(QVector3D edge_color) {
  std::cout << "edge color : " << edge_color[0] << " " << edge_color[1] << " " << edge_color[2] << std::endl;
  view_->ChangeEdgeColor(edge_color);
}

}  // namespace s21

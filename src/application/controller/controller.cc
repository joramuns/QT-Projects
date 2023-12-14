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
}

void Controller::ControllerTransformSlot(double value, char axis, int type) {
  std::cout << (type ? axis == 'S' ? "Scale " : "Move " : "Rotate ")
            << "tab: " << axis << " " << value << " " << std::endl;
  if (type == ROTATE) {
    view_->Rotate(value, axis);
  } else if (type == MOVE) {
    view_->Move(value, axis);
  } else if (type == SCALE) {
    view_->Scale(value);
  }
}

void Controller::ControllerOpenFileSlot(QString filename) {
  std::cout << "Open file " << filename.toStdString() << std::endl;
  ObjectModel a = fasade_->AddModel(filename.toStdString());
  std::vector<GLfloat> vertices;
  for (const auto &item : a.GetVertices()) {
    vertices.insert(vertices.end(), item.begin(), item.end());
  }
  std::vector<GLuint> indices;
  for (const auto &item : a.GetVertexIndexes()) {
    indices.insert(indices.end(), item.begin(), item.end());
  }
  view_->LoadModel(vertices, indices);
  view_->AddListWidgetItem(filename);
}

void Controller::ControllerCloseFileSlot(int model_number) {
  if (fasade_->CountModel()) {
    fasade_->RemoveModel(model_number);
    view_->UnloadModel(model_number);
  }
}

}  // namespace s21

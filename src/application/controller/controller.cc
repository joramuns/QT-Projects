#include "controller.h"

namespace s21 {
Controller::Controller(View *v, Facade *f) : view_(v), facade_(f) {
  ConnectFields();
}

void Controller::ControllerTransformSlot(double value, char axis, int type,
                                         int model_number) {
  if (facade_->GetCountModel() && model_number >= 0) {
    if (type == ROTATE) {
      facade_->Rotate(value, axis, model_number);
    } else if (type == MOVE) {
      facade_->Move(value, axis, model_number);
    } else if (type == SCALE) {
      facade_->Scale(value, model_number);
    }
  }
}

void Controller::ControllerOpenFileSlot(QString filename) {
  if (filename.size()) {
    std::string model_info = facade_->AddModel(filename.toStdString());
    view_->AddListWidgetItem(model_info);
  }
}

void Controller::ControllerCloseFileSlot(int model_number) {
  if (facade_->GetCountModel()) {
    facade_->RemoveModel(model_number);
    view_->RemoveListWidgetItem(model_number);
  }
}

void Controller::ControllerSceneOptionSlot(int index) {
  facade_->SwitchProjection(index);
}

void Controller::ControllerExtraSceneOptionSlot(int index) {
  facade_->SwitchWireframe(index);
}

void Controller::ControllerSceneColor(QColor scene_color) {
  facade_->ChangeSceneColor(scene_color);
}

void Controller::ControllerVertexColor(QVector3D vertex_color) {
  facade_->ChangeVertexColor(vertex_color);
}

void Controller::ControllerEdgeColor(QVector3D edge_color) {
  facade_->ChangeEdgeColor(edge_color);
}

void Controller::ControllerVertexOption(int index) {
  facade_->ChangeVertexOption(index);
}

void Controller::ControllerEdgeOption(int index) {
  facade_->ChangeEdgeOption(index);
}

void Controller::ControllerVertexSize(double value) {
  facade_->ChangeVertexSize(value);
}

void Controller::ControllerEdgeSize(double value) {
  facade_->ChangeEdgeSize(value);
}

void Controller::ControllerScreenshotSlot(const QString &filename) {
  facade_->TakeScreenshot(filename);
}

void Controller::ControllerGifSlot(const QString &filename) {
  facade_->TakeGif(filename);
}

void Controller::ConnectFields() const {
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

  connect(view_, &View::VertexOptionSignal, this,
          &Controller::ControllerVertexOption);

  connect(view_, &View::EdgeOptionSignal, this,
          &Controller::ControllerEdgeOption);

  connect(view_, &View::VertexSizeSignal, this,
          &Controller::ControllerVertexSize);

  connect(view_, &View::EdgeSizeSignal, this, &Controller::ControllerEdgeSize);

  connect(view_, &View::ScreenshotSignal, this,
          &Controller::ControllerScreenshotSlot);

  connect(view_, &View::GifSignal, this,
          &Controller::ControllerGifSlot);
}

}  // namespace s21

#include "settings_singleton.h"

SettingsSingleton::SettingsSingleton()
    : current_path_(QCoreApplication::applicationDirPath()),
      settings_(current_path_ + "/config.ini", QSettings::IniFormat) {
  ReadSettings();
}

SettingsSingleton &SettingsSingleton::GetInstance() {
  static SettingsSingleton instance;
  return instance;
}

const QColor &SettingsSingleton::GetBGColor() const noexcept {
  return bg_color_;
}

const QVector3D &SettingsSingleton::GetVertexColor() const noexcept {
  return vert_color_;
}

const QVector3D &SettingsSingleton::GetEdgeColor() const noexcept {
  return edge_color_;
}

bool SettingsSingleton::GetProjectionType() const noexcept {
  return central_projection_;
}

bool SettingsSingleton::GetPolygonType() const noexcept { return solid_; }

int SettingsSingleton::GetVertexType() const noexcept { return vert_type_; }

GLfloat SettingsSingleton::GetVertexSize() const noexcept { return vert_size_; }

GLfloat SettingsSingleton::GetEdgeSize() const noexcept { return edge_size_; }

bool SettingsSingleton::GetEdgeType() const noexcept { return dashed_lines_; }

void SettingsSingleton::WriteSettings() {
  settings_.setValue("background color", bg_color_);
  settings_.setValue("vertex color", vert_color_);
  settings_.setValue("edge color", edge_color_);
  settings_.setValue("central projection", central_projection_);
  settings_.setValue("solid", solid_);
  settings_.setValue("vertex type", vert_type_);
  settings_.setValue("vertex size", vert_size_);
  settings_.setValue("edge size", edge_size_);
  settings_.setValue("dashed lines", dashed_lines_);
  settings_.setValue("HALO", 0);
}

void SettingsSingleton::ReadSettings() {
  bg_color_ =
      settings_.value("background color", QColor(0, 0, 0)).value<QColor>();
  vert_color_ = settings_.value("vertex color", QVector3D(255, 255, 255))
                    .value<QVector3D>();
  edge_color_ =
      settings_.value("edge color", QVector3D(0, 255, 0)).value<QVector3D>();
  central_projection_ = settings_.value("central projection").toBool();
  solid_ = settings_.value("solid").toBool();
  vert_type_ = settings_.value("vertex type").toInt();
  vert_size_ = settings_.value("vertex size").toFloat();
  edge_size_ = settings_.value("edge size").toFloat();
  dashed_lines_ = settings_.value("dashed lines").toBool();
}

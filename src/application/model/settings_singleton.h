#ifndef CPP4_3DVIEWER_V2_0_2_APPLICATION_VIEW_SETTINGS_SINGLETON_H_
#define CPP4_3DVIEWER_V2_0_2_APPLICATION_VIEW_SETTINGS_SINGLETON_H_

#include <QOpenGLWidget>
#include <QApplication>
#include <QSettings>
#include <QVector3D>

class SettingsSingleton {
 public:
  static SettingsSingleton &GetInstance();

  SettingsSingleton(const SettingsSingleton &other) = delete;
  SettingsSingleton(SettingsSingleton &&other) = delete;
  SettingsSingleton &operator=(const SettingsSingleton &other) = delete;
  SettingsSingleton &operator=(SettingsSingleton &&other) = delete;
  ~SettingsSingleton() = default;

  const QColor &GetBGColor() const noexcept;      
  const QVector3D &GetVertexColor() const noexcept;
  const QVector3D &GetEdgeColor() const noexcept;
  bool GetProjectionType() const noexcept;
  bool GetPolygonType() const noexcept;
  int GetVertexType() const noexcept;
  GLfloat GetVertexSize() const noexcept;
  GLfloat GetEdgeSize() const noexcept;
  bool GetEdgeType() const noexcept;
  void WriteSettings();
  const QColor &GetBGColor(const QColor &color) const noexcept;      
  const QVector3D &GetVertexColor() const noexcept;
  const QVector3D &GetEdgeColor() const noexcept;
  bool GetProjectionType() const noexcept;
  bool GetPolygonType() const noexcept;
  int GetVertexType() const noexcept;
  GLfloat GetVertexSize() const noexcept;
  GLfloat GetEdgeSize() const noexcept;
  bool GetEdgeType() const noexcept;

 private:
  SettingsSingleton();
  void ReadSettings();

 private:
  QString current_path_;
  QSettings settings_;
  QColor bg_color_;          ///< цвет сцены
  QVector3D vert_color_;     ///< цвет вершин
  QVector3D edge_color_;     ///< цвет ребер
  bool central_projection_;  ///< тип проекции
  bool solid_;               ///< тип отображения
  int vert_type_;            ///< тип отображения вершин
  GLfloat vert_size_;  ///< значение величины отображаемых вершин
  GLfloat edge_size_;  ///< значение величины отображаемых ребер
  bool dashed_lines_;  ///< тип отображения ребер
};

#endif  // CPP4_3DVIEWER_V2_0_2_APPLICATION_VIEW_SETTINGS_SINGLETON_H_

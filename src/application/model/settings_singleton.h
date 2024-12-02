/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса SettingsSingleton
*/
#ifndef CPP4_3DVIEWER_V2_0_2_APPLICATION_VIEW_SETTINGS_SINGLETON_H_
#define CPP4_3DVIEWER_V2_0_2_APPLICATION_VIEW_SETTINGS_SINGLETON_H_

#include <QApplication>
#include <QOpenGLWidget>
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

  void WriteSettings();

  /* Accessors */
  inline const QColor &GetBGColor() const noexcept { return bg_color_; };
  inline const QVector3D &GetVertexColor() const noexcept {
    return vert_color_;
  };
  inline const QVector3D &GetEdgeColor() const noexcept { return edge_color_; };
  inline bool GetProjectionType() const noexcept {
    return central_projection_;
  };
  inline int GetPolygonType() const noexcept { return solid_; };
  inline int GetVertexType() const noexcept { return vert_type_; };
  inline GLfloat GetVertexSize() const noexcept { return vert_size_; };
  inline GLfloat GetEdgeSize() const noexcept { return edge_size_; };
  inline bool GetEdgeType() const noexcept { return dashed_lines_; };
  inline const QVector3D &GetLightColor() const noexcept {
    return light_color_;
  }
  inline const QVector3D &GetLightPosition() const noexcept {
    return light_pos_;
  }

  /* Mutators */
  inline void SetBGColor(const QColor &color) noexcept { bg_color_ = color; };
  inline void SetVertexColor(const QVector3D &color) noexcept {
    vert_color_ = color;
  };
  inline void SetEdgeColor(const QVector3D &color) noexcept {
    edge_color_ = color;
  };
  inline void SetProjectionType(const bool setter) noexcept {
    central_projection_ = setter;
  };
  inline void SetPolygonType(const bool setter) noexcept { solid_ = setter; };
  inline void SetVertexType(const int setter) noexcept { vert_type_ = setter; };
  inline void SetVertexSize(const GLfloat value) noexcept {
    vert_size_ = value;
  };
  inline void SetEdgeSize(const GLfloat value) noexcept { edge_size_ = value; };
  inline void SetEdgeType(const bool setter) noexcept {
    dashed_lines_ = setter;
  };
  inline void SetLightPosition(const QVector3D pos) noexcept {
    light_pos_ = pos;
  }
  inline void SetLightColor(const QVector3D color) noexcept {
    light_color_ = color;
  }

 private:
  SettingsSingleton();
  void ReadSettings();

 private:
  QString current_path_;
  QSettings settings_;
  QColor bg_color_;       ///< цвет сцены
  QVector3D vert_color_;  ///< цвет вершин
  QVector3D edge_color_;  ///< цвет ребер
  QVector3D light_pos_;
  QVector3D light_color_;
  bool central_projection_;  ///< тип проекции
  int solid_;                ///< тип отображения
  int vert_type_;            ///< тип отображения вершин
  GLfloat vert_size_;  ///< значение величины отображаемых вершин
  GLfloat edge_size_;  ///< значение величины отображаемых ребер
  bool dashed_lines_;  ///< тип отображения ребер
};

#endif  // CPP4_3DVIEWER_V2_0_2_APPLICATION_VIEW_SETTINGS_SINGLETON_H_

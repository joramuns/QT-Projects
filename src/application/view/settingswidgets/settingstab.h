#ifndef VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_
#define VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_

#include <QTabWidget>

#include "settings.h"

namespace s21 {
class SettingsTab final : public QTabWidget {
  Q_OBJECT

 public:
  SettingsTab();

 public slots:
  void SceneColorSlot();
  void VertexColorSlot();
  void EdgeColorSlot();
  void SceneOptionSlot(const QString &index);
  void VertexOptionSlot(const QString &index);
  void EdgeOptionSlot(const QString &index);
  void VertexSizeSlot(double value);
  void EdgeSizeSlot(double value);

 signals:
  void TabSceneColorSignal();
  void TabVertexColorSignal();
  void TabEdgeColorSignal();
  void TabSceneOptionSignal(const QString &index);
  void TabVertexOptionSignal(const QString &index);
  void TabEdgeOptionSignal(const QString &index);
  void TabVertexSizeSignal(double value);
  void TabEdgeSizeSignal(double value);

 private:
  SceneSettings *scene_settings_;
  ModelSettings *vertex_settings_;
  ModelSettings *edge_settings_;
};
}  // namespace s21

#endif  // VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_

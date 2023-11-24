#ifndef VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_
#define VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_

#include <QTabWidget>

#include "settings.h"

namespace s21 {
class SettingsTab final : public QTabWidget {
  Q_OBJECT

 public:
  SettingsTab();

 private:
  SceneSettings *scene_settings_;
  ModelSettings *vertex_settings_;
  ModelSettings *edge_settings_;
};
}  // namespace s21

#endif  // VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_

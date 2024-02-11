#ifndef VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_
#define VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_

#include <QColorDialog>
#include <QTabWidget>
#include <QVector3D>

#include "settings.h"

namespace s21 {
/// @brief Класс определяющий инициализацию вкладок настроек
class SettingsTab final : public QTabWidget {
  Q_OBJECT

public:
  /// @brief Конструктор по умолачанию, инициализирует поля, подключает сигналы
  /// с обработчиками, добавляет вкладки настроек на "макет" интерфейса
  SettingsTab();

public slots:
  void SceneColorSlot();
  void VertexColorSlot();
  void EdgeColorSlot();
  void SceneOptionSlot(int index);
  void ExtraSceneOptionSlot(int index);
  void VertexOptionSlot(int index);
  void EdgeOptionSlot(int index);
  void VertexSizeSlot(double value);
  void EdgeSizeSlot(double value);

signals:
  void TabSceneColorSignal(QColor scene_color);
  void TabVertexColorSignal(QVector3D vertex_color);
  void TabEdgeColorSignal(QVector3D edge_color);
  void TabSceneOptionSignal(int index);
  void TabExtraSceneOptionSignal(int index);
  void TabVertexOptionSignal(int index);
  void TabEdgeOptionSignal(int index);
  void TabVertexSizeSignal(double value);
  void TabEdgeSizeSignal(double value);

private:
  ExtraSceneSettings *scene_settings_;
  ModelSettings *vertex_settings_;
  ModelSettings *edge_settings_;
};
} // namespace s21

#endif // VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_

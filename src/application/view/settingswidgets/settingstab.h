#ifndef VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_
#define VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_

#include <QColorDialog>
#include <QTabWidget>
#include <QVector3D>

#include "settings.h"
#include "../../model/settings_singleton.h"

namespace s21 {
/// @brief Класс определяющий инициализацию вкладок настроек
class SettingsTab final : public QTabWidget {
  Q_OBJECT

public:
  /// @brief Конструктор по умолачанию, инициализирует поля, подключает сигналы
  /// с обработчиками, добавляет вкладки настроек на "макет" интерфейса
  SettingsTab();

public slots:
  /// @brief Слот выпускающий сигнал смены цвета сцены
  void SceneColorSlot();
  /// @brief Слот выпускающий сигнал смены цвета вершин
  void VertexColorSlot();
  /// @brief Слот выпускающий сигнал смены цвета ребер
  void EdgeColorSlot();
  /// @brief Слот выпускающий сигнал смены типа проекции
  /// @param index Тип проекции
  void SceneOptionSlot(int index);
  /// @brief Слот выпускающий сигнал смены типа отображения граней
  /// @param index Тип отображения граней
  void ExtraSceneOptionSlot(int index);
  /// @brief Слот выпускающий сигнал смены типа отображения вершин
  /// @param index тип отображения вершн
  void VertexOptionSlot(int index);
  /// @brief Слот выпускающий сигнал смены типа отображения ребер
  /// @param index тип отображения ребер
  void EdgeOptionSlot(int index);
  /// @brief Слот выпускающий сигнал смены величины отображения вершин
  /// @param value величина отображения вершин
  void VertexSizeSlot(double value);
  /// @brief Слот выпускающий сигнал смены величины отображения граней
  /// @param value величина отображения граней
  void EdgeSizeSlot(double value);

signals:
  /// @brief Сигнал смены цвета сцены
  /// @param scene_color цвет сцены
  void TabSceneColorSignal(QColor scene_color);
  /// @brief Сигнал смены цвета вершин
  /// @param vertex_color цвет вершин
  void TabVertexColorSignal(QVector3D vertex_color);
  /// @brief Сигнал смены цвета ребер
  /// @param edge_color цвет ребер
  void TabEdgeColorSignal(QVector3D edge_color);
  /// @brief Сигнал смены типа проекции
  /// @param index тип проекции 
  void TabSceneOptionSignal(int index);
  /// @brief Сигнал смены типа отображения граней
  /// @param index тип ототображения граней
  void TabExtraSceneOptionSignal(int index);
  /// @brief Сигнал смены типа оторажения вершин
  /// @param index тип отображения вершин
  void TabVertexOptionSignal(int index);
  /// @brief Сигнал смены типа отображения ребер
  /// @param index тип отображения ребер
  void TabEdgeOptionSignal(int index);
  /// @brief Сигнал смены величины отображения вершин
  /// @param value величина оторажения вершин
  void TabVertexSizeSignal(double value);
  /// @brief Сигнал смены величины отображения ребер
  /// @param value величина отображения ребер
  void TabEdgeSizeSignal(double value);

private:
  /// @brief Иницилизация вкладок настроек
  void InitFields();

  /// @brief Подключение сигналов к обработчикам
  void ConnectFields();

  /// @brief Вынесение вкладок на  "макет" интерфейса
  void AddTab();

  void ReadSettings();

private:
  ExtraSceneSettings *scene_settings_; ///< указатель на виджет управления отображением 3-х мерного объекта
  ModelSettings *vertex_settings_;     ///< указатель на виджет управления отображением вершин
  ModelSettings *edge_settings_;       ///< указатель на вилжет управления отображением ребер
};
} // namespace s21

#endif // VIEW_SETTINGSWIDGETS_SETTINGSTAB_H_
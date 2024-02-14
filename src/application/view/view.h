#ifndef VIEW_H_
#define VIEW_H_

#include <QCloseEvent>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

// temp glwidget
#include "../model/context/glwidget.h"
#include "mainwidgets/app_management.h"
#include "settingswidgets/settingstab.h"
#include "transformwidgets/transform_tab.h"

namespace s21 {
/// @brief Класс верхнего уровня пользовательсокого интерфейса, который
/// организовывает инициализацию, коннекты и расположение управляющих элементов
/// интерфейса для пользователя
class View final : public QWidget {
  Q_OBJECT

 public:
  View() = delete;
  ~View();
  /// @brief
  /// @param context
  explicit View(GLWidget *context);

  void AddListWidgetItem(const QString filename);
  void RemoveListWidgetItem(int model_number);

 private slots:
  void ViewTransformSlot(double value, char axis, int type, int model_number);
  void OpenFileSlot(QString filename);
  void CloseFileSlot();
  void SceneOptionSlot(int index);
  void ExtraSceneOptionSlot(int index);
  void SceneColorSlot(QColor scene_color);
  void VertexColorSlot(QVector3D vertex_color);
  void EdgeColorSlot(QVector3D edge_color);
  void VertexOptionSlot(int index);
  void EdgeOptionSlot(int index);
  void VertexSizeSlot(double value);
  void EdgeSizeSlot(double value);
  void ScreenshotSlot(const QString &filename);

 signals:
  void ViewTransformSignal(double value, char axis, int type, int model_number);
  void OpenFileSignal(QString filename);
  void CloseFileSignal(int model_number);
  void SceneOptionSignal(int index);
  void ExtraSceneOptionSignal(int index);
  void SceneColorSignal(QColor scene_color);
  void VertexColorSignal(QVector3D vertex_color);
  void EdgeColorSignal(QVector3D edge_color);
  void VertexOptionSignal(int index);
  void EdgeOptionSignal(int index);
  void VertexSizeSignal(double value);
  void EdgeSizeSignal(double value);
  void ScreenshotSignal(const QString &filename);

 private:
  void closeEvent(QCloseEvent *event);

 private:
  QGridLayout *main_layout_;
  GLWidget *gl_widget_;
  QListWidget *list_widget_;
};
}  // namespace s21

#endif  // VIEW_H_

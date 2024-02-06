#ifndef VIEW_H_
#define VIEW_H_

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "app_management.h"
#include "opengl/glwidget.h"
#include "settingswidgets/settingstab.h"
#include "transformwidgets/transform_tab.h"

namespace s21 {
class View final : public QWidget {
  Q_OBJECT

 public:
  View();

  void LoadModel(std::vector<GLfloat> vertices);
  void UnloadModel(int model_number);
  void Rotate(double value, char axis, int model_number);
  void Move(double value, char axis, int model_number);
  void Scale(double value, int model_number);
  void AddListWidgetItem(const QString filename);
  void RemoveListWidgetItem(int model_number);
  void SwitchProjection(int index);
  void SwitchWireframe(int index);
  void ChangeSceneColor(QColor scene_color);
  void ChangeVertexColor(QVector3D vertex_color);
  void ChangeEdgeColor(QVector3D edge_color);
  void ChangeVertexOption(int index);
  void ChangeEdgeOption(int index);

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

 private:
  QGridLayout *main_layout_;
  GLWidget *gl_widget_;
  QListWidget *list_widget_;
};
}  // namespace s21

#endif  // VIEW_H_

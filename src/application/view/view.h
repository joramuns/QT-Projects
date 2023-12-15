#ifndef VIEW_H_
#define VIEW_H_

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QListWidget>

#include "app_management.h"
#include "opengl/glwidget.h"
#include "settingswidgets/settingstab.h"
#include "transformwidgets/transform_tab.h"

namespace s21 {
class View final : public QWidget {
  Q_OBJECT

 public:
  View();

  void LoadModel(std::vector<GLfloat> vertices, std::vector<GLuint> vertex_indices, std::vector<GLfloat> normals, std::vector<GLuint> normal_indices);
  void UnloadModel(int model_number);
  void Rotate(double value, char axis, int model_number);
  void Move(double value, char axis, int model_number);
  void Scale(double value, int model_number);
  void AddListWidgetItem(const QString filename);
  void RemoveListWidgetItem(int model_number);

 private slots:
  void ViewTransformSlot(double value, char axis, int type, int model_number);
  void OpenFileSlot(QString filename);
  void CloseFileSlot();

 signals:
  void ViewTransformSignal(double value, char axis, int type, int model_number);
  void OpenFileSignal(QString filename);
  void CloseFileSignal(int model_number);

 private:
  QGridLayout *main_layout_;
  GLWidget *gl_widget_;
  QListWidget *list_widget_;
};
}  // namespace s21

#endif  // VIEW_H_

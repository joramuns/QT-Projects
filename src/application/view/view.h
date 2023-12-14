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

  void LoadModel(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
  void UnloadModel(int model_number);
  void Rotate(double value, char axis);
  void Move(double value, char axis);
  void Scale(double value);
  void AddListWidgetItem(const QString filename);
  void RemoveListWidgetItem(int model_number);

 private slots:
  void ViewTransformSlot(double value, char axis, int type);
  void OpenFileSlot(QString filename);
  void CloseFileSlot();

 signals:
  void ViewTransformSignal(double value, char axis, int type);
  void OpenFileSignal(QString filename);
  void CloseFileSignal(int model_number);

 private:
  QGridLayout *main_layout_;
  GLWidget *gl_widget_;
  QListWidget *list_widget_;
};
}  // namespace s21

#endif  // VIEW_H_

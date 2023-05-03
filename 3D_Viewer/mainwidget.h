#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include "draw.h"
#include "mybutton.h"
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QDir>

#define S21_PI 3.141592

class MainWidget : public QWidget {
  Q_OBJECT
public:
  MainWidget();
  ~MainWidget();
  Draw *m_paint_widget;
  void closeEvent(QCloseEvent *event);
  void saveSettings();
  void readSettings();

private:

  const char *file_name;


  int tik;
  QTimer *timer;
  QString filePath;

  MyButton *x_minus;
  MyButton *x_plus;
  MyButton *y_minus;
  MyButton *y_plus;
  MyButton *z_minus;
  MyButton *z_plus;

  MyButton *x_clockwise;
  MyButton *x_counterclockwise;
  MyButton *y_clockwise;
  MyButton *y_counterclockwise;
  MyButton *z_clockwise;
  MyButton *z_counterclockwise;

  MyButton *scale_plus_button;
  MyButton *scale_minus_button;

  MyButton *file_select;

  MyButton *bg_color_select;
  MyButton *vertex_color_select;
  MyButton *faces_color_select;

  MyButton *screenshot;
  MyButton *screencast;

  QCheckBox *dashed_face;

  QCheckBox *projection_type;
  QDoubleSpinBox *vertex_size;
  QSpinBox *line_size;
  QComboBox *vertex_type;

  // need delete in destruct
  QLabel *fakelabel_0;
  QLabel *vertex_type_name;
  QLabel *vertex_size_name;
  QLabel *line_size_name;
  QLabel *movement_step_name;
  QLabel *rotation_angle_name;
  QLabel *zoom_step_name;

  QLabel *model_name;
  QLabel *size_of_array;
  QLabel *size_of_edges;
  QLabel *model_pre_name;

  QDoubleSpinBox *movement_step;
  QDoubleSpinBox *rotation_angle;
  QDoubleSpinBox *zoom_step;

  MyButton *createButton(QString text);
  QGridLayout *m_main_layout;

private Q_SLOTS:
  void left_move();
  void right_move();
  void up_move();
  void down_move();
  void in_move();
  void out_move();
  void turn_x();
  void turn_counter_x();
  void turn_y();
  void turn_counter_y();
  void turn_z();
  void turn_counter_z();
  void scale_plus();
  void scale_minus();

  void togglePref(PrefMask mask);
  void handleComboBox(const QString &input);

  void bg_select_color();
  void vertex_select_color();
  void faces_select_color();

  void select_file();
  void screen_shooter();
  void screen_caster();
  void timerTick();
};

#endif // MAINWIDGET_H

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "draw.h"
#include "mybutton.h"
#include <QGridLayout>
#include <QWidget>
#include <QCheckBox>

class MainWidget : public QWidget {
  Q_OBJECT
public:
  MainWidget();
  Draw *m_paint_widget;

private:
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

  MyButton *scale_plus;
  MyButton *scale_minus;

  MyButton *file_select;
  

  MyButton *createButton(QString text);
  QGridLayout *m_main_layout;
};

#endif // MAINWIDGET_H

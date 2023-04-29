#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include "draw.h"
#include "mybutton.h"

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
    MyButton *x_minus;
    MyButton *x_plus;
    MyButton *y_minus;
    MyButton *y_plus;

    MyButton *x_clockwise;
    MyButton *x_counterclockwise;
    MyButton *y_clockwise;
    MyButton *y_counterclockwise;
    MyButton *z_clockwise;
    MyButton *z_counterclockwise;

    MyButton *scale_plus;
    MyButton *scale_minus;
    
    MyButton *file_select;

    MyButton *bg_color_select;
    MyButton *vertex_color_select;
    MyButton *faces_color_select;

    MyButton *dashed_face;

    QCheckBox *projection_type;
    QDoubleSpinBox *vertex_size;
    QSpinBox *line_size;
    QComboBox *vertex_type;

    MyButton *createButton(QString text);
    QGridLayout *m_main_layout;

  MyButton *createButton(QString text);
  QGridLayout *m_main_layout;
};

#endif // MAINWIDGET_H

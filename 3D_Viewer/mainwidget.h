#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "mybutton.h"
#include "paint.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget();
private:
    MyButton *createButton(QString text);
    QGridLayout *m_main_layout;
    Paint *m_paint_widget;

};

#endif // MAINWIDGET_H

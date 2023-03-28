#ifndef GENLAYOUT_H
#define GENLAYOUT_H

#include "mainwindow.h"
#include <QGridLayout>

class GenLayout : public QWidget
{
    Q_OBJECT
private:
    MainWindow *m_window;
    QGridLayout *m_layout;
public:
    GenLayout();
};

#endif // GENLAYOUT_H

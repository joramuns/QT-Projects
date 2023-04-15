#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget h;
    h.show();
    int end = a.exec();
    free(h.m_paint_widget->point_array);
    return end;
}


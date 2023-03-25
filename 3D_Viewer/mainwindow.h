#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>

class MainWindow
{
public:
    MainWindow();
private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
};

#endif // MAINWINDOW_H

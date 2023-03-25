#include "mainwindow.h"

MainWindow::MainWindow()
{
    m_scene = new QGraphicsScene();
    m_view = new QGraphicsView();

    m_view->setRenderHint(QPainter::Antialiasing);

    QPolygonF polygon;
    polygon << QPointF(0, 0) << QPointF(150, 10) << QPointF(20, 20);

    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(polygon);
    polygonItem->setPen(QPen(Qt::black, 2));
    polygonItem->setBrush(QBrush(Qt::white));

    m_scene->addItem(polygonItem);
    m_view->setScene(m_scene);
    m_view->show();

}

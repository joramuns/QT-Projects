#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<float> point1;
    QVector<float> point2;
    QVector<float> point3;
private:
        void initializeGL() override;
        void paintGL() override;
public slots:
        void update();
};

#endif // MAINWINDOW_H

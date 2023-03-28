#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>

class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QVector<float> point1;
    QVector<float> point2;
    QVector<float> point3;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QTimer m_timer;

private slots:
    void my_slot();
};

#endif // MAINWINDOW_H

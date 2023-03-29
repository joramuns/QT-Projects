#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>
#include <QGridLayout>
#include "mybutton.h"

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
    QGridLayout *m_layout;
    MyButton *createButton(QString text);

public slots:
    void my_slot();
    void left_move();
};

#endif // MAINWINDOW_H

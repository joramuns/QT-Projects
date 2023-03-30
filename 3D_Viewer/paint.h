#ifndef PAINT_H
#define PAINT_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTimer>
#include <QGridLayout>

class Paint : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT;
public:
    explicit Paint(QWidget *parent = nullptr);
    QVector<float> point1;
    QVector<float> point2;
    QVector<float> point3;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QTimer m_timer;
    QGridLayout *m_layout;

public Q_SLOTS:
    void my_slot();
    void left_move();
};

#endif // PAINT_H

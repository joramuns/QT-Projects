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
    float x_scale;
    float y_scale;
    float z_scale;
    QTimer m_timer;
    QGridLayout *m_layout;
    QVector<float>scaling(float x, float y, float z, QVector<float> point);

public Q_SLOTS:
    void left_move();
    void right_move();
    void up_move();
    void down_move();
};

#endif // PAINT_H

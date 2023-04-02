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
    QVector<float> point4;
    QVector<float> point5;
    QVector<float> point6;
    QVector<float> point7;
    QVector<float> point8;
    QVector<float> point9;
    QVector<float> point10;
    QVector<float> point11;
    QVector<float> point12;
    QVector<float> point13;
    QVector<float> point14;
    QVector<float> point15;
    QVector<float> point16;
    QVector<float> point17;
    QVector<float> point18;
    QVector<float> point19;
    QVector<float> point20;
    QVector<float> point21;
    QVector<float> point22;
    QVector<float> point23;
    QVector<float> point24;
    QVector<float> point25;
    QVector<float> point26;
    QVector<float> point27;
    QVector<float> point28;
    QVector<float> point29;
    QVector<float> point30;
    QVector<float> point31;
    QVector<float> point32;
    QVector<float> point33;
    QVector<float> point34;
    QVector<float> point35;
    QVector<float> point36;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QVector<float>coordinate_change(float x, float y, float z, QVector<float> point);
    QVector<float> turn_matrix_x(float theta, QVector<float> point);
    QVector<float> turn_matrix_y(float theta, QVector<float> point);
    QVector<float> turn_matrix_z(float theta, QVector<float> point);
    QVector<float> scaling(float x, QVector<float> point);

    void curent_move(float x, float y, float z);

    void curent_turn_x(float theta);
    void curent_turn_y(float theta);
    void curent_turn_z(float theta);
public Q_SLOTS:
    void left_move();
    void right_move();
    void up_move();
    void down_move();

    void turn_x();
    void turn_counter_x();
    void turn_y();
    void turn_counter_y();
    void turn_z();
    void turn_counter_z();

    void scale_plus();
    void scale_minus();
};

#endif // PAINT_H

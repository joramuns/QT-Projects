#include "paint.h"

Paint::Paint(QWidget *parent)
    :QOpenGLWidget(parent){
    this->setWindowTitle("3D_View");
    point1 = {-1.0, -1.0, 0.0, 1};
    point2 = {1.0, -1.0, 0.0, 1};
    point3 = {0.0, 1.0, 0.0, 1};

}

QVector<float> Paint::scaling(float x, float y, float z, QVector<float> point)
{
    QVector<QVector<float>> matrix_scale(4, QVector<float>(4));
    matrix_scale[0][0] = 1;
    matrix_scale[0][1] = 0;
    matrix_scale[0][2] = 0;
    matrix_scale[0][3] = x;
    matrix_scale[1][0] = 0;
    matrix_scale[1][1] = 1;
    matrix_scale[1][2] = 0;
    matrix_scale[1][3] = y;
    matrix_scale[2][0] = 0;
    matrix_scale[2][1] = 0;
    matrix_scale[2][2] = 1;
    matrix_scale[2][3] = z;
    matrix_scale[3][0] = 0;
    matrix_scale[3][1] = 0;
    matrix_scale[3][2] = 0;
    matrix_scale[3][3] = 1;
    QVector<float> result(4);
        for (int i = 0; i < 4; i++) {
            float sum = 0.0f;
            for (int j = 0; j < 4; j++) {
                sum += matrix_scale[i][j] *  point[j];
            }
            result[i] = sum;
        }
    return result;
}

void Paint::left_move()
{
    point1 = scaling(-0.01, 0.0, 0.0, point1);
    point2 = scaling(-0.01, 0.0, 0.0, point2);
    point3 = scaling(-0.01, 0.0, 0.0, point3);

    repaint();
}

void Paint::right_move()
{
    point1 = scaling(0.01, 0.0, 0.0, point1);
    point2 = scaling(0.01, 0.0, 0.0, point2);
    point3 = scaling(0.01, 0.0, 0.0, point3);

    repaint();
}

void Paint::up_move()
{
    point1 = scaling(0.0, 0.01, 0.0, point1);
    point2 = scaling(0.0, 0.01, 0.0, point2);
    point3 = scaling(0.0, 0.01, 0.0, point3);

    repaint();
}

void Paint::down_move()
{
    point1 = scaling(0.0, -0.01, 0.0, point1);
    point2 = scaling(0.0, -0.01, 0.0, point2);
    point3 = scaling(0.0, -0.01, 0.0, point3);

    repaint();
}

void Paint::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    this->resize(800, 600);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Paint::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Paint::paintGL()
{
    glClearColor(0.00f, 0.808f, 0.820f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
//    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(point1[0], point1[1], point1[2]);
    glVertex3f(point2[0], point2[1], point2[2]);
    glVertex3f(point3[0], point3[1], point3[2]);
        glEnd();
}


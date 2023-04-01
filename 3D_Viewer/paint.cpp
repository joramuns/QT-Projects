#include "paint.h"
#include <GL/glu.h>

#define SHIFT 0.03

Paint::Paint(QWidget *parent)
    :QOpenGLWidget(parent){
    point1 = {-1.0, -1.0, -1.0, 1};
    point2 = {-1.0, 1.0, -1.0, 1};
    point3 = {1.0, 1.0, -1.0, 1};

}

void Paint::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-2, 2, -2, 2, -2, 2);
    glFrustum(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    this->resize(800, 600);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Paint::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Paint::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
//    glColor3f(1.0f, 0.0f, 0.0f);
    //front
    glVertex3f(point1[0], point1[1], point1[2]);
    glVertex3f(point2[0], point2[1], point2[2]);
    glVertex3f(point3[0], point3[1], point3[2]);

    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1, -1, -1);
    //rigth_side
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, 1);

    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1, -1, -1);
    //down
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    //left_side
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, -1);

    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    //up
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    //back
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);

    glVertex3f(-1, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1, -1, 1);

        glEnd();
}

QVector<float> Paint::coordinate_change(float x,
                                        float y,
                                        float z,
                                        QVector<float> point)
{
    QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

    matrix_scale[0][0] = 1.0;
    matrix_scale[0][1] = 0.0;
    matrix_scale[0][2] = 0.0;
    matrix_scale[0][3] = x;

    matrix_scale[1][0] = 0.0;
    matrix_scale[1][1] = 1.0;
    matrix_scale[1][2] = 0.0;
    matrix_scale[1][3] = y;

    matrix_scale[2][0] = 0.0;
    matrix_scale[2][1] = 0.0;
    matrix_scale[2][2] = 1.0;
    matrix_scale[2][3] = z;

    matrix_scale[3][0] = 0.0;
    matrix_scale[3][1] = 0.0;
    matrix_scale[3][2] = 0.0;
    matrix_scale[3][3] = 1.0;

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


void Paint::curent_move(float x, float y, float z) {
    point1 = coordinate_change(x, y, z, point1);
    point2 = coordinate_change(x, y, z, point2);
    point3 = coordinate_change(x, y, z, point3);
}

void Paint::left_move() {
    curent_move(-SHIFT, 0.0, 0.0);
    repaint();
}

void Paint::right_move()
{
    curent_move(SHIFT, 0.0, 0.0);
    repaint();
}

void Paint::up_move()
{
    curent_move(0.0, SHIFT, 0.0);
    repaint();
}

void Paint::down_move()
{
    curent_move(0.0, -SHIFT, 0.0);
    repaint();
}


QVector<float> Paint::turn_matrix_x(float theta,
                                    QVector<float> point) {
    QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

    matrix_scale[0][0] = 1.0;
    matrix_scale[0][1] = 0.0;
    matrix_scale[0][2] = 0.0;
    matrix_scale[0][3] = 0.0;

    matrix_scale[1][0] = 0.0;
    matrix_scale[1][1] = cos(theta);
    matrix_scale[1][2] = -sin(theta);
    matrix_scale[1][3] = 0.0;

    matrix_scale[2][0] = 0.0;
    matrix_scale[2][1] = sin(theta);
    matrix_scale[2][2] = cos(theta);
    matrix_scale[2][3] = 0.0;

    matrix_scale[3][0] = 0.0;
    matrix_scale[3][1] = 0.0;
    matrix_scale[3][2] = 0.0;
    matrix_scale[3][3] = 1.0;

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

void Paint::curent_turn_x(float theta) {
    point1 = turn_matrix_x(theta, point1);
    point2 = turn_matrix_x(theta, point2);
    point3 = turn_matrix_x(theta, point3);
}

void Paint::turn_x() {
    curent_turn_x(SHIFT);
    repaint();
}

void Paint::turn_counter_x(){
    curent_turn_x(-SHIFT);
    repaint();
}

QVector<float> Paint::turn_matrix_y(float theta,
                                    QVector<float> point) {
    QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

    matrix_scale[0][0] = cos(theta);
    matrix_scale[0][1] = 0.0;
    matrix_scale[0][2] = sin(theta);
    matrix_scale[0][3] = 0.0;

    matrix_scale[1][0] = 0.0;
    matrix_scale[1][1] = 1.0;
    matrix_scale[1][2] = 0.0;
    matrix_scale[1][3] = 0.0;

    matrix_scale[2][0] = -sin(theta);
    matrix_scale[2][1] = 0.0;
    matrix_scale[2][2] = cos(theta);
    matrix_scale[2][3] = 0.0;

    matrix_scale[3][0] = 0.0;
    matrix_scale[3][1] = 0.0;
    matrix_scale[3][2] = 0.0;
    matrix_scale[3][3] = 1.0;

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

void Paint::curent_turn_y(float theta) {
    point1 = turn_matrix_y(theta, point1);
    point2 = turn_matrix_y(theta, point2);
    point3 = turn_matrix_y(theta, point3);
}

void Paint::turn_y() {
    curent_turn_y(SHIFT);
    repaint();
}

void Paint::turn_counter_y(){
    curent_turn_y(-SHIFT);
    repaint();
}

QVector<float> Paint::turn_matrix_z(float theta,
                                    QVector<float> point) {
    QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

    matrix_scale[0][0] = cos(theta);
    matrix_scale[0][1] = -sin(theta);
    matrix_scale[0][2] = 0.0;
    matrix_scale[0][3] = 0.0;

    matrix_scale[1][0] = sin(theta);
    matrix_scale[1][1] = cos(theta);
    matrix_scale[1][2] = 0.0;
    matrix_scale[1][3] = 0.0;

    matrix_scale[2][0] = 0.0;
    matrix_scale[2][1] = 0.0;
    matrix_scale[2][2] = 1.0;
    matrix_scale[2][3] = 0.0;

    matrix_scale[3][0] = 0.0;
    matrix_scale[3][1] = 0.0;
    matrix_scale[3][2] = 0.0;
    matrix_scale[3][3] = 1.0;

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

void Paint::curent_turn_z(float theta) {
    point1 = turn_matrix_z(theta, point1);
    point2 = turn_matrix_z(theta, point2);
    point3 = turn_matrix_z(theta, point3);
}

void Paint::turn_z() {
    curent_turn_z(SHIFT);
    repaint();
}

void Paint::turn_counter_z(){
    curent_turn_z(-SHIFT);
    repaint();
}


QVector<float> Paint::scaling(float x,
                              QVector<float> point)
{
    QVector<QVector<float>> matrix_scale(4, QVector<float>(4));

    matrix_scale[0][0] = x;
    matrix_scale[0][1] = 0.0;
    matrix_scale[0][2] = 0.0;
    matrix_scale[0][3] = 0.0;

    matrix_scale[1][0] = 0.0;
    matrix_scale[1][1] = x;
    matrix_scale[1][2] = 0.0;
    matrix_scale[1][3] = 0.0;

    matrix_scale[2][0] = 0.0;
    matrix_scale[2][1] = 0.0;
    matrix_scale[2][2] = x;
    matrix_scale[2][3] = 0.0;

    matrix_scale[3][0] = 0.0;
    matrix_scale[3][1] = 0.0;
    matrix_scale[3][2] = 0.0;
    matrix_scale[3][3] = 1.0;

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

void Paint::scale_plus()
{
    point1 = scaling(1 + SHIFT, point1);
    point2 = scaling(1 + SHIFT, point2);
    point3 = scaling(1 + SHIFT, point3);
    repaint();
}

void Paint::scale_minus()
{
    point1 = scaling(1 - SHIFT, point1);
    point2 = scaling(1 - SHIFT, point2);
    point3 = scaling(1 - SHIFT, point3);
    repaint();
}

#include "paint.h"
#if defined(__APPLE__)
  #include <OpenGL/glu.h>
#elif defined(__unix__)
  #include <GL/glu.h>
#endif
#include <math.h>

#define SHIFT 0.03

Paint::Paint(QWidget *parent)
    :QOpenGLWidget(parent){
    point1 = {-0.5, -0.5, -0.5, 1};
    point2 = {-0.5, 0.5, -0.5, 1};
    point3 = {0.5, 0.5, -0.5, 1};
    point4 = {0.5, 0.5, -0.5, 1};
    point5 = {0.5, -0.5, -0.5, 1};
    point6 = {-0.5, -0.5, -0.5, 1};
    point7 = {0.5, 0.5, -0.5, 1};
    point8 = {0.5, -0.5, -0.5, 1};
    point9 = {0.5, 0.5, 0.5, 1};
    point10 = {0.5, 0.5, 0.5, 1};
    point11 = {0.5, -0.5, 0.5, 1};
    point12 = {0.5, -0.5, -0.5, 1};
    point13 = {0.5, -0.5, 0.5, 1};
    point14 = {0.5, -0.5, -0.5, 1};
    point15 = {-0.5, -0.5, -0.5, 1};
    point16 = {0.5, -0.5, 0.5, 1};
    point17 = {-0.5, -0.5, -0.5, 1};
    point18 = {-0.5, -0.5, 0.5, 1};
    point19 = {-0.5, -0.5, -0.5, 1};
    point20 = {-0.5, -0.5, 0.5, 1};
    point21 = {-0.5, 0.5, -0.5, 1};
    point22 = {-0.5, 0.5, -0.5, 1};
    point23 = {-0.5, -0.5, 0.5, 1};
    point24 = {-0.5, 0.5, 0.5, 1};
    point25 = {-0.5, 0.5, -0.5, 1};
    point26 = {0.5, 0.5, -0.5, 1};
    point27 = {0.5, 0.5, 0.5, 1};
    point28 = {-0.5, 0.5, -0.5, 1};
    point29 = {-0.5, 0.5, 0.5, 1};
    point30 = {0.5, 0.5, 0.5, 1};
    point31 = {-0.5, 0.5, 0.5, 1};
    point32 = {0.5, 0.5, 0.5, 1};
    point33 = {0.5, -0.5, 0.5, 1};
    point34 = {-0.5, 0.5, 0.5, 1};
    point35 = {-0.5, -0.5, 0.5, 1};
    point36 = {0.5, -0.5, 0.5, 1};

}

void Paint::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);



    this->resize(800, 800);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Paint::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-1, 1, -1, 1, -1, 2);
    //glFrustum(-1, 1, -1, 1, 0.5, 5);
    gluPerspective(60, 1, 0.5, 100);
}

void Paint::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -2);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    //front
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(point1[0], point1[1], point1[2]);
    glVertex3f(point2[0], point2[1], point2[2]);
    glVertex3f(point3[0], point3[1], point3[2]);

    glVertex3f(point4[0], point4[1], point4[2]);
    glVertex3f(point5[0], point5[1], point5[2]);
    glVertex3f(point6[0], point6[1], point6[2]);
    //rigth_side
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(point7[0], point7[1], point7[2]);
    glVertex3f(point8[0], point8[1], point8[2]);
    glVertex3f(point9[0], point9[1], point9[2]);

    glVertex3f(point10[0], point10[1], point10[2]);
    glVertex3f(point11[0], point11[1], point11[2]);
    glVertex3f(point12[0], point12[1], point12[2]);
    //down
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(point13[0], point13[1], point13[2]);
    glVertex3f(point14[0], point14[1], point14[2]);
    glVertex3f(point15[0], point15[1], point15[2]);

    glVertex3f(point16[0], point16[1], point16[2]);
    glVertex3f(point17[0], point17[1], point17[2]);
    glVertex3f(point18[0], point18[1], point18[2]);
    //left_side
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(point19[0], point19[1], point19[2]);
    glVertex3f(point20[0], point20[1], point20[2]);
    glVertex3f(point21[0], point21[1], point21[2]);

    glVertex3f(point22[0], point22[1], point22[2]);
    glVertex3f(point23[0], point23[1], point23[2]);
    glVertex3f(point24[0], point24[1], point24[2]);
    //up
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(point25[0], point25[1], point25[2]);
    glVertex3f(point26[0], point26[1], point26[2]);
    glVertex3f(point27[0], point27[1], point27[2]);

    glVertex3f(point28[0], point28[1], point28[2]);
    glVertex3f(point29[0], point29[1], point29[2]);
    glVertex3f(point30[0], point30[1], point30[2]);
    //back
    glColor3f(1.0f, 0.5f, 0.5f);
    glVertex3f(point31[0], point31[1], point31[2]);
    glVertex3f(point32[0], point32[1], point32[2]);
    glVertex3f(point33[0], point33[1], point33[2]);

    glVertex3f(point34[0], point34[1], point34[2]);
    glVertex3f(point35[0], point35[1], point35[2]);
    glVertex3f(point36[0], point36[1], point36[2]);

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
    point4 = coordinate_change(x, y, z, point4);
    point5 = coordinate_change(x, y, z, point5);
    point6 = coordinate_change(x, y, z, point6);
    point7 = coordinate_change(x, y, z, point7);
    point8 = coordinate_change(x, y, z, point8);
    point9 = coordinate_change(x, y, z, point9);
    point10 = coordinate_change(x, y, z, point10);
    point11 = coordinate_change(x, y, z, point11);
    point12 = coordinate_change(x, y, z, point12);
    point13 = coordinate_change(x, y, z, point13);
    point14 = coordinate_change(x, y, z, point14);
    point15 = coordinate_change(x, y, z, point15);
    point16 = coordinate_change(x, y, z, point16);
    point17 = coordinate_change(x, y, z, point17);
    point18 = coordinate_change(x, y, z, point18);
    point19 = coordinate_change(x, y, z, point19);
    point20 = coordinate_change(x, y, z, point20);
    point21 = coordinate_change(x, y, z, point21);
    point22 = coordinate_change(x, y, z, point22);
    point23 = coordinate_change(x, y, z, point23);
    point24 = coordinate_change(x, y, z, point24);
    point25 = coordinate_change(x, y, z, point25);
    point26 = coordinate_change(x, y, z, point26);
    point27 = coordinate_change(x, y, z, point27);
    point28 = coordinate_change(x, y, z, point28);
    point29 = coordinate_change(x, y, z, point29);
    point30 = coordinate_change(x, y, z, point30);
    point31 = coordinate_change(x, y, z, point31);
    point32 = coordinate_change(x, y, z, point32);
    point33 = coordinate_change(x, y, z, point33);
    point34 = coordinate_change(x, y, z, point34);
    point35 = coordinate_change(x, y, z, point35);
    point36 = coordinate_change(x, y, z, point36);
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
    point4 = turn_matrix_x(theta, point4);
    point5 = turn_matrix_x(theta, point5);
    point6 = turn_matrix_x(theta, point6);
    point7 = turn_matrix_x(theta, point7);
    point8 = turn_matrix_x(theta, point8);
    point9 = turn_matrix_x(theta, point9);
    point10 = turn_matrix_x(theta, point10);
    point11 = turn_matrix_x(theta, point11);
    point12 = turn_matrix_x(theta, point12);
    point13 = turn_matrix_x(theta, point13);
    point14 = turn_matrix_x(theta, point14);
    point15 = turn_matrix_x(theta, point15);
    point16 = turn_matrix_x(theta, point16);
    point17 = turn_matrix_x(theta, point17);
    point18 = turn_matrix_x(theta, point18);
    point19 = turn_matrix_x(theta, point19);
    point20 = turn_matrix_x(theta, point20);
    point21 = turn_matrix_x(theta, point21);
    point22 = turn_matrix_x(theta, point22);
    point23 = turn_matrix_x(theta, point23);
    point24 = turn_matrix_x(theta, point24);
    point25 = turn_matrix_x(theta, point25);
    point26 = turn_matrix_x(theta, point26);
    point27 = turn_matrix_x(theta, point27);
    point28 = turn_matrix_x(theta, point28);
    point29 = turn_matrix_x(theta, point29);
    point30 = turn_matrix_x(theta, point30);
    point31 = turn_matrix_x(theta, point31);
    point32 = turn_matrix_x(theta, point32);
    point33 = turn_matrix_x(theta, point33);
    point34 = turn_matrix_x(theta, point34);
    point35 = turn_matrix_x(theta, point35);
    point36 = turn_matrix_x(theta, point36);
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
    point4 = turn_matrix_y(theta, point4);
    point5 = turn_matrix_y(theta, point5);
    point6 = turn_matrix_y(theta, point6);
    point7 = turn_matrix_y(theta, point7);
    point8 = turn_matrix_y(theta, point8);
    point9 = turn_matrix_y(theta, point9);
    point10 = turn_matrix_y(theta, point10);
    point11 = turn_matrix_y(theta, point11);
    point12 = turn_matrix_y(theta, point12);
    point13 = turn_matrix_y(theta, point13);
    point14 = turn_matrix_y(theta, point14);
    point15 = turn_matrix_y(theta, point15);
    point16 = turn_matrix_y(theta, point16);
    point17 = turn_matrix_y(theta, point17);
    point18 = turn_matrix_y(theta, point18);
    point19 = turn_matrix_y(theta, point19);
    point20 = turn_matrix_y(theta, point20);
    point21 = turn_matrix_y(theta, point21);
    point22 = turn_matrix_y(theta, point22);
    point23 = turn_matrix_y(theta, point23);
    point24 = turn_matrix_y(theta, point24);
    point25 = turn_matrix_y(theta, point25);
    point26 = turn_matrix_y(theta, point26);
    point27 = turn_matrix_y(theta, point27);
    point28 = turn_matrix_y(theta, point28);
    point29 = turn_matrix_y(theta, point29);
    point30 = turn_matrix_y(theta, point30);
    point31 = turn_matrix_y(theta, point31);
    point32 = turn_matrix_y(theta, point32);
    point33 = turn_matrix_y(theta, point33);
    point34 = turn_matrix_y(theta, point34);
    point35 = turn_matrix_y(theta, point35);
    point36 = turn_matrix_y(theta, point36);
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
    point4 = turn_matrix_z(theta, point4);
    point5 = turn_matrix_z(theta, point5);
    point6 = turn_matrix_z(theta, point6);
    point7 = turn_matrix_z(theta, point7);
    point8 = turn_matrix_z(theta, point8);
    point9 = turn_matrix_z(theta, point9);
    point10 = turn_matrix_z(theta, point10);
    point11 = turn_matrix_z(theta, point11);
    point12 = turn_matrix_z(theta, point12);
    point13 = turn_matrix_z(theta, point13);
    point14 = turn_matrix_z(theta, point14);
    point15 = turn_matrix_z(theta, point15);
    point16 = turn_matrix_z(theta, point16);
    point17 = turn_matrix_z(theta, point17);
    point18 = turn_matrix_z(theta, point18);
    point19 = turn_matrix_z(theta, point19);
    point20 = turn_matrix_z(theta, point20);
    point21 = turn_matrix_z(theta, point21);
    point22 = turn_matrix_z(theta, point22);
    point23 = turn_matrix_z(theta, point23);
    point24 = turn_matrix_z(theta, point24);
    point25 = turn_matrix_z(theta, point25);
    point26 = turn_matrix_z(theta, point26);
    point27 = turn_matrix_z(theta, point27);
    point28 = turn_matrix_z(theta, point28);
    point29 = turn_matrix_z(theta, point29);
    point30 = turn_matrix_z(theta, point30);
    point31 = turn_matrix_z(theta, point31);
    point32 = turn_matrix_z(theta, point32);
    point33 = turn_matrix_z(theta, point33);
    point34 = turn_matrix_z(theta, point34);
    point35 = turn_matrix_z(theta, point35);
    point36 = turn_matrix_z(theta, point36);
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
    point4 = scaling(1 + SHIFT, point4);
    point5 = scaling(1 + SHIFT, point5);
    point6 = scaling(1 + SHIFT, point6);
    point7 = scaling(1 + SHIFT, point7);
    point8 = scaling(1 + SHIFT, point8);
    point9 = scaling(1 + SHIFT, point9);
    point10 = scaling(1 + SHIFT, point10);
    point11 = scaling(1 + SHIFT, point11);
    point12 = scaling(1 + SHIFT, point12);
    point13 = scaling(1 + SHIFT, point13);
    point14 = scaling(1 + SHIFT, point14);
    point15 = scaling(1 + SHIFT, point15);
    point16 = scaling(1 + SHIFT, point16);
    point17 = scaling(1 + SHIFT, point17);
    point18 = scaling(1 + SHIFT, point18);
    point19 = scaling(1 + SHIFT, point19);
    point20 = scaling(1 + SHIFT, point20);
    point21 = scaling(1 + SHIFT, point21);
    point22 = scaling(1 + SHIFT, point22);
    point23 = scaling(1 + SHIFT, point23);
    point24 = scaling(1 + SHIFT, point24);
    point25 = scaling(1 + SHIFT, point25);
    point26 = scaling(1 + SHIFT, point26);
    point27 = scaling(1 + SHIFT, point27);
    point28 = scaling(1 + SHIFT, point28);
    point29 = scaling(1 + SHIFT, point29);
    point30 = scaling(1 + SHIFT, point30);
    point31 = scaling(1 + SHIFT, point31);
    point32 = scaling(1 + SHIFT, point32);
    point33 = scaling(1 + SHIFT, point33);
    point34 = scaling(1 + SHIFT, point34);
    point35 = scaling(1 + SHIFT, point35);
    point36 = scaling(1 + SHIFT, point36);

    repaint();
}

void Paint::scale_minus()
{
    point1 = scaling(1 - SHIFT, point1);
    point2 = scaling(1 - SHIFT, point2);
    point3 = scaling(1 - SHIFT, point3);
    point4 = scaling(1 - SHIFT, point4);
    point5 = scaling(1 - SHIFT, point5);
    point6 = scaling(1 - SHIFT, point6);
    point7 = scaling(1 - SHIFT, point7);
    point8 = scaling(1 - SHIFT, point8);
    point9 = scaling(1 - SHIFT, point9);
    point10 = scaling(1 - SHIFT, point10);
    point11 = scaling(1 - SHIFT, point11);
    point12 = scaling(1 - SHIFT, point12);
    point13 = scaling(1 - SHIFT, point13);
    point14 = scaling(1 - SHIFT, point14);
    point15 = scaling(1 - SHIFT, point15);
    point16 = scaling(1 - SHIFT, point16);
    point17 = scaling(1 - SHIFT, point17);
    point18 = scaling(1 - SHIFT, point18);
    point19 = scaling(1 - SHIFT, point19);
    point20 = scaling(1 - SHIFT, point20);
    point21 = scaling(1 - SHIFT, point21);
    point22 = scaling(1 - SHIFT, point22);
    point23 = scaling(1 - SHIFT, point23);
    point24 = scaling(1 - SHIFT, point24);
    point25 = scaling(1 - SHIFT, point25);
    point26 = scaling(1 - SHIFT, point26);
    point27 = scaling(1 - SHIFT, point27);
    point28 = scaling(1 - SHIFT, point28);
    point29 = scaling(1 - SHIFT, point29);
    point30 = scaling(1 - SHIFT, point30);
    point31 = scaling(1 - SHIFT, point31);
    point32 = scaling(1 - SHIFT, point32);
    point33 = scaling(1 - SHIFT, point33);
    point34 = scaling(1 - SHIFT, point34);
    point35 = scaling(1 - SHIFT, point35);
    point36 = scaling(1 - SHIFT, point36);

    repaint();
}

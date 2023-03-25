#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QOpenGLWidget(parent)
{
    point1 = {-1.0, -1.0, 0.0};
    point2 = {1.0, -1.0, 0.0};
    point3 = {0.0, 1.0, 0.0};

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000 / 60);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    //glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(point1[0], point1[1], point1[2]);
    //glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(point2[0], point2[1], point2[2]);
    //glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(point3[0], point3[1], point3[2]);
    glEnd();
}

void MainWindow::update()
{
    float a = 0.9;
        float b = 0.9;

        QVector<QVector<float>> matrix_scale(3, QVector<float>(3));
        matrix_scale[0][0] = a;
        matrix_scale[0][1] = 0;
        matrix_scale[0][2] = 0;
        matrix_scale[1][0] = 0;
        matrix_scale[1][1] = b;
        matrix_scale[1][2] = 0;
        matrix_scale[2][0] = 0;
        matrix_scale[2][1] = 0;
        matrix_scale[2][2] = 1;

        QVector<float> result(3);
        for (int i = 0; i < 3; i++) {
            float sum = 0.0f;
            for (int j = 0; j < 3; j++) {
                sum += matrix_scale[i][j] * point1[j];
            }
            result[i] = sum;
        }
        point1 = result;

        update();
}

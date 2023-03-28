#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QOpenGLWidget(parent){
    this->setWindowTitle("3D_View");
    point1 = {-1.0, -1.0, 0.0};
    point2 = {1.0, -1.0, 0.0};
    point3 = {0.0, 1.0, 0.0};

    m_timer.start(33);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(my_slot()));

}

void MainWindow::my_slot()
{
//    for (int i = 0; i < 3; ++i){
//        point1[i] *= 0.9;
//    }
    repaint();
}

void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    this->resize(800, 600);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MainWindow::paintGL()
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


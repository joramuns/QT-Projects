#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget h;
    h.show();
//    QGridLayout *test = new QGridLayout();
//    QWidget *main = new QWidget();
//    main->setLayout(test);
//    main->resize(1024, 800);
//    Paint h;
//    test->addWidget(&h, 0, 0, 8, 6);
//    main->show();
    return a.exec();
}


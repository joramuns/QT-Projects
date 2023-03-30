#include "mainwidget.h"
#include <QLabel>

MainWidget::MainWidget()
{
    m_main_layout = new QGridLayout();
    m_paint_widget = new Paint();

    this->setLayout(m_main_layout);
    this->resize(1024, 800);


    MyButton *x_minus = createButton("Left");
    connect(x_minus, &QPushButton::clicked, m_paint_widget, &Paint::left_move);
    MyButton *x_plus = createButton("Right");
    connect(x_plus, &QPushButton::clicked, m_paint_widget, &Paint::right_move);
    MyButton *y_plus = createButton("Up");
    connect(y_plus, &QPushButton::clicked, m_paint_widget, &Paint::up_move);
    MyButton *y_minus = createButton("Down");
    connect(y_minus, &QPushButton::clicked, m_paint_widget, &Paint::down_move);

    m_main_layout->addWidget(m_paint_widget, 0, 0, 8, 16);
    QLabel *fake_label = new QLabel("");
    m_main_layout->addWidget(fake_label, 8, 0, 1, 16);
    m_main_layout->addWidget(x_minus, 10, 0, 3, 2);
    m_main_layout->addWidget(x_plus, 10, 3, 3, 2);
    m_main_layout->addWidget(y_plus, 10, 6, 3, 2);
    m_main_layout->addWidget(y_minus, 10, 10, 3, 2);
}

MyButton* MainWidget::createButton(QString text) {
    MyButton *button = new MyButton(text);
    return button;
}

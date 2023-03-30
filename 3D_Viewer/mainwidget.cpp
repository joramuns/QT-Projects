#include "mainwidget.h"

MainWidget::MainWidget()
{
    m_main_layout = new QGridLayout();
    m_paint_widget = new Paint();

    this->setLayout(m_main_layout);
    this->resize(1024, 800);


    MyButton *x_minus = createButton("Left");
    connect(x_minus, &QPushButton::clicked, m_paint_widget, &Paint::left_move);

    m_main_layout->addWidget(m_paint_widget, 0, 0, 8, 8);
    m_main_layout->addWidget(x_minus, 8, 0, 1, 2);
}

MyButton* MainWidget::createButton(QString text) {
    MyButton *button = new MyButton(text);
    return button;
}

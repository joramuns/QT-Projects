#include "mainwidget.h"
#include <QLabel>
#include <QFileDialog>

MainWidget::MainWidget()
{
    m_main_layout = new QGridLayout();
    m_paint_widget = new Draw();

    this->setLayout(m_main_layout);
    this->resize(1024, 1024);

    x_minus = createButton("Left");
    x_minus->setShortcut(QKeySequence(Qt::Key_Left));
    connect(x_minus, &QPushButton::clicked, m_paint_widget, &Draw::left_move);

    x_plus = createButton("Right");
    x_plus->setShortcut(QKeySequence(Qt::Key_Right));
    connect(x_plus, &QPushButton::clicked, m_paint_widget, &Draw::right_move);

    y_plus = createButton("Up");
    y_plus->setShortcut(QKeySequence(Qt::Key_Up));
    connect(y_plus, &QPushButton::clicked, m_paint_widget, &Draw::up_move);

    y_minus = createButton("Down");
    y_minus->setShortcut(QKeySequence(Qt::Key_Down));
    connect(y_minus, &QPushButton::clicked, m_paint_widget, &Draw::down_move);

    x_clockwise = createButton("Rotate x");// QKeySequence(Qt::Key_9
    x_clockwise->setShortcut(QKeySequence(Qt::Key_7));
    connect(x_clockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_x);

    x_counterclockwise = createButton("Rotate -x");
    x_counterclockwise->setShortcut(QKeySequence(Qt::Key_8));
    connect(x_counterclockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_counter_x);

    y_clockwise = createButton("Rotate y");
    y_clockwise->setShortcut(QKeySequence(Qt::Key_4)); 
    connect(y_clockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_y);

    y_counterclockwise = createButton("Rotate -y");
    y_counterclockwise->setShortcut(QKeySequence(Qt::Key_5));
    connect(y_counterclockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_counter_y);

    z_clockwise = createButton("Rotate z");
    z_clockwise->setShortcut(QKeySequence(Qt::Key_1));
    connect(z_clockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_z);

    z_counterclockwise = createButton("Rotate -z");
    z_counterclockwise->setShortcut(QKeySequence(Qt::Key_2));
    connect(z_counterclockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_counter_z);

    scale_plus = createButton("+");
    scale_plus->setShortcut(QKeySequence(Qt::Key_Plus));
    connect(scale_plus, &QPushButton::clicked, m_paint_widget, &Draw::scale_plus);

    scale_minus = createButton("-");
    scale_minus->setShortcut(QKeySequence(Qt::Key_Minus));
    connect(scale_minus, &QPushButton::clicked, m_paint_widget, &Draw::scale_minus);

    file_select = createButton("Select File");
    connect(file_select, &QPushButton::clicked, m_paint_widget, &Draw::select_file);

    bg_color_select = createButton("Choose background color");
    connect(bg_color_select, &QPushButton::clicked, m_paint_widget, &Draw::bg_select_color);

    vertex_color_select = createButton("Choose vertex color");
    connect(vertex_color_select, &QPushButton::clicked, m_paint_widget, &Draw::vertex_select_color);

    faces_color_select = createButton("Choose face color");
    connect(faces_color_select, &QPushButton::clicked, m_paint_widget, &Draw::faces_select_color);
    
    show_vertex = createButton("Show vertex");
    connect(show_vertex, &QPushButton::clicked, m_paint_widget, [=]() { m_paint_widget->toggle_pref(kVertex); });

    dashed_face = createButton("Dashed lines");
    connect(dashed_face, &QPushButton::clicked, m_paint_widget, [=]() { m_paint_widget->toggle_pref(kDashed); });

    squared_rounded_vertex = createButton("Shape of vertex");
    connect(squared_rounded_vertex, &QPushButton::clicked, m_paint_widget, [=]() { m_paint_widget->toggle_pref(kSquareVertex); });

    vertex_size = new QSpinBox(this);
    vertex_size->setRange(1, 20);
    vertex_size->setValue(m_paint_widget->getVertexSize());
    connect(vertex_size, &QSpinBox::valueChanged, m_paint_widget, [=]() { m_paint_widget->setVertexSize(vertex_size->value()); });

    line_size = new QSpinBox(this);
    line_size->setRange(1, 20);
    line_size->setValue(m_paint_widget->getLineSize());
    connect(line_size, &QSpinBox::valueChanged, m_paint_widget, [=]() { m_paint_widget->setLineSize(line_size->value()); });

    m_main_layout->addWidget(m_paint_widget,        0, 0, 18, 20);

    m_main_layout->addWidget(x_minus,               18, 0,  2, 2);
    m_main_layout->addWidget(x_plus,                18, 2,  2, 2);
    m_main_layout->addWidget(y_plus,                18, 4,  2, 2);
    m_main_layout->addWidget(y_minus,               18, 6,  2, 2);
    m_main_layout->addWidget(x_clockwise,           18, 8,  1, 2);
    m_main_layout->addWidget(x_counterclockwise,    19, 8,  1, 2);
    m_main_layout->addWidget(y_clockwise,           18, 10, 1, 2);
    m_main_layout->addWidget(y_counterclockwise,    19, 10, 1, 2);
    m_main_layout->addWidget(z_clockwise,           18, 12, 1, 2);
    m_main_layout->addWidget(z_counterclockwise,    19, 12, 1, 2);
    m_main_layout->addWidget(scale_plus,            18, 18, 2, 1);
    m_main_layout->addWidget(scale_minus,           18, 19, 2, 1);
    m_main_layout->addWidget(file_select,           20,  1, 2, 1);
    m_main_layout->addWidget(bg_color_select,       20,  3, 2, 1);
    m_main_layout->addWidget(vertex_color_select,   20,  5, 2, 1);
    m_main_layout->addWidget(faces_color_select,    20,  7, 2, 1);
    m_main_layout->addWidget(show_vertex,           20,  9, 2, 1);
    m_main_layout->addWidget(dashed_face,           20,  11, 2, 1);
    m_main_layout->addWidget(squared_rounded_vertex,       20,  13, 2, 1);
    m_main_layout->addWidget(vertex_size, 21, 0, 4, 1);
    m_main_layout->addWidget(line_size, 21, 10, 4, 1);

    //QString fileName = QFileDialog::getOpenFileName(this, tr("Выберите файл"), "/home", tr("Файлы (*)"));

    this->setWindowTitle("3D_View");
}

MainWidget::~MainWidget() {
  delete m_main_layout;
  delete m_paint_widget;
  delete x_minus;
  delete x_plus;
  delete y_minus;
  delete y_plus;

  delete x_clockwise;
  delete x_counterclockwise;
  delete y_clockwise;
  delete y_counterclockwise;
  delete z_clockwise;
  delete z_counterclockwise;

  delete scale_plus;
  delete scale_minus;
  
  delete file_select;
  delete bg_color_select;
  delete vertex_color_select;
  delete faces_color_select;

  delete show_vertex;
  delete vertex_size;
  delete line_size;
}

MyButton* MainWidget::createButton(QString text) {
    MyButton *button = new MyButton(text);
    return button;
}


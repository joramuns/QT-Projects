#define GL_SILENCE_DEPRECATION
#include "mainwidget.h"
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QSettings>

MainWidget::MainWidget() {
  m_main_layout = new QGridLayout();
  m_paint_widget = new Draw();

  setLayout(m_main_layout);
  resize(1024, 1024);

  readSettings();

  x_minus = createButton(QChar(0x00002190));
  x_minus->setStyleSheet("font: 20pt");
  x_minus->setShortcut(QKeySequence(Qt::Key_Left));
  x_minus->setShortcut(QKeySequence(Qt::Key_A));
  connect(x_minus, &QPushButton::clicked, m_paint_widget, &Draw::left_move);

  x_plus = createButton(QChar(0x00002192));
  x_plus->setStyleSheet("font: 20pt");
  x_plus->setShortcut(QKeySequence(Qt::Key_Right));
  x_plus->setShortcut(QKeySequence(Qt::Key_D));
  connect(x_plus, &QPushButton::clicked, m_paint_widget, &Draw::right_move);

  y_plus = createButton(QChar(0x00002191));
  y_plus->setStyleSheet("font:20pt");
  y_plus->setShortcut(QKeySequence(Qt::Key_Up));
  y_plus->setShortcut(QKeySequence(Qt::Key_W));
  connect(y_plus, &QPushButton::clicked, m_paint_widget, &Draw::up_move);

  y_minus = createButton(QChar(0x00002193));
  y_minus->setStyleSheet("font:20pt");
  y_minus->setShortcut(QKeySequence(Qt::Key_Down));
  y_minus->setShortcut(QKeySequence(Qt::Key_S));
  connect(y_minus, &QPushButton::clicked, m_paint_widget, &Draw::down_move);

  z_plus = createButton(QChar(0x00002350));
  z_plus->setStyleSheet("font:20pt");
  z_plus->setShortcut(QKeySequence(Qt::Key_E));
  connect(z_plus, &QPushButton::clicked, m_paint_widget, &Draw::in_move);

  z_minus = createButton(QChar(0x00002357));
  z_minus->setStyleSheet("font:20pt");
  z_minus->setShortcut(QKeySequence(Qt::Key_Q));
  connect(z_minus, &QPushButton::clicked, m_paint_widget, &Draw::out_move);

  x_clockwise = createButton('X' + QChar(0x000027F3));
  x_clockwise->setStyleSheet("font:20pt");
  x_clockwise->setShortcut(QKeySequence(Qt::Key_8));
  connect(x_clockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_x);

  x_counterclockwise = createButton('X' + QChar(0x000027F2));
  x_counterclockwise->setStyleSheet("font:20pt");
  x_counterclockwise->setShortcut(QKeySequence(Qt::Key_7));
  connect(x_counterclockwise, &QPushButton::clicked, m_paint_widget,
          &Draw::turn_counter_x);

  y_clockwise = createButton('Y'+ QChar(0x000027F3));
  y_clockwise->setStyleSheet("font:20pt");
  y_clockwise->setShortcut(QKeySequence(Qt::Key_5));
  connect(y_clockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_y);

  y_counterclockwise = createButton('Y'+ QChar(0x000027F2));
  y_counterclockwise->setStyleSheet("font:20pt");
  y_counterclockwise->setShortcut(QKeySequence(Qt::Key_4));
  connect(y_counterclockwise, &QPushButton::clicked, m_paint_widget,
          &Draw::turn_counter_y);

  z_clockwise = createButton('Z'+ QChar(0x000027F3));
  z_clockwise->setStyleSheet("font:20pt");
  z_clockwise->setShortcut(QKeySequence(Qt::Key_2));
  connect(z_clockwise, &QPushButton::clicked, m_paint_widget, &Draw::turn_z);

  z_counterclockwise = createButton('Z'+ QChar(0x000027F2));
  z_counterclockwise->setStyleSheet("font:20pt");
  z_counterclockwise->setShortcut(QKeySequence(Qt::Key_1));
  connect(z_counterclockwise, &QPushButton::clicked, m_paint_widget,
          &Draw::turn_counter_z);

  scale_plus = createButton(QChar(0x0000002B));
  scale_plus->setStyleSheet("font:20pt");
  scale_plus->setShortcut(QKeySequence(Qt::Key_Plus));
  connect(scale_plus, &QPushButton::clicked, m_paint_widget, &Draw::scale_plus);

  scale_minus = createButton(QChar(0x00002212));
  scale_minus->setStyleSheet("font:20pt");
  scale_minus->setShortcut(QKeySequence(Qt::Key_Minus));
  connect(scale_minus, &QPushButton::clicked, m_paint_widget,
          &Draw::scale_minus);

  file_select = createButton("File selection");
  file_select->setStyleSheet("font:18pt");
  connect(file_select, &QPushButton::clicked, m_paint_widget,
          &Draw::select_file);

  bg_color_select = createButton("Choose background color");
  bg_color_select->setStyleSheet("font:18pt");
  connect(bg_color_select, &QPushButton::clicked, m_paint_widget,
          &Draw::bg_select_color);

  vertex_color_select = createButton("Choose vertex color");
  vertex_color_select->setStyleSheet("font:18pt");
  connect(vertex_color_select, &QPushButton::clicked, m_paint_widget,
          &Draw::vertex_select_color);

  faces_color_select = createButton("Choose face color");
  faces_color_select->setStyleSheet("font:18pt");
  connect(faces_color_select, &QPushButton::clicked, m_paint_widget,
          &Draw::faces_select_color);

  dashed_face = new QCheckBox("Dashed lines");
  dashed_face->setStyleSheet("font:20pt");
  connect(dashed_face, &QPushButton::clicked, m_paint_widget,
          [=]() { m_paint_widget->togglePref(kDashed); });

  projection_type = new QCheckBox("Perspective", this);
  projection_type->setStyleSheet("font:20pt");
  projection_type->setCheckState(
      m_paint_widget->getPref(kProjection) ? Qt::Unchecked : Qt::Checked);
  connect(projection_type, &QCheckBox::stateChanged, m_paint_widget,
          [=]() { m_paint_widget->togglePref(kProjection); });

  vertex_size = new QDoubleSpinBox(this);
  vertex_size->setRange(1, 20);
  vertex_size->setValue(m_paint_widget->preferences.v_size);
  vertex_size->setKeyboardTracking(false);
  vertex_size->setFocusPolicy(Qt::NoFocus);
  vertex_size->resize(1, 4);
  vertex_size->setAlignment(Qt::AlignRight);
  vertex_size->setSingleStep(0.5);
  connect(vertex_size, &QDoubleSpinBox::valueChanged, m_paint_widget, [=]() {
    m_paint_widget->preferences.v_size = vertex_size->value();
    m_paint_widget->update();
  });

  line_size = new QSpinBox(this);
  line_size->setRange(1, 20);
  line_size->setValue(m_paint_widget->preferences.l_size);
  line_size->setFocusPolicy(Qt::NoFocus);
  line_size->resize(1, 4);
  line_size->setAlignment(Qt::AlignRight);
  connect(line_size, &QSpinBox::valueChanged, m_paint_widget, [=]() {
    m_paint_widget->preferences.l_size = line_size->value();
    m_paint_widget->update();
  });

  vertex_type = new QComboBox(this);
  vertex_type->addItem("None");
  vertex_type->addItem("Round");
  vertex_type->addItem("Square");
  if (!m_paint_widget->getPref(kVertex)) {
    vertex_type->setCurrentIndex(0);
  } else if (!m_paint_widget->getPref(kSquareVertex)) {
    vertex_type->setCurrentIndex(1);
  } else {
    vertex_type->setCurrentIndex(2);
  }
  connect(vertex_type, &QComboBox::currentTextChanged, m_paint_widget,
          [=](const QString &vertex_type_text) {
            m_paint_widget->handleComboBox(vertex_type_text);
          });

  QLabel *fakelabel_0 = new QLabel("");
  fakelabel_0->setStyleSheet("font:22pt");

  QLabel *vertex_type_name = new QLabel("Vertex type:");
  vertex_type_name->setStyleSheet("font:20pt");

  QLabel *vertex_size_name = new QLabel("Vertex size:");
  vertex_size_name->setStyleSheet("font:20pt");

  QLabel *line_size_name = new QLabel("Line size:");
  line_size_name->setStyleSheet("font:20pt");

  m_main_layout->addWidget(m_paint_widget,        0, 0, 20, 20);
  m_main_layout->addWidget(x_minus,               21, 0, 1, 1);
  m_main_layout->addWidget(x_plus,                21, 2, 1, 1);
  m_main_layout->addWidget(y_plus,                20, 1, 1, 1);
  m_main_layout->addWidget(y_minus,               21, 1, 1, 1);
  m_main_layout->addWidget(z_plus,                20, 2, 1, 1);
  m_main_layout->addWidget(z_minus,               20, 0, 1, 1);
  m_main_layout->addWidget(x_clockwise,           20, 4, 1, 1);
  m_main_layout->addWidget(x_counterclockwise,    21, 4, 1, 1);
  m_main_layout->addWidget(y_clockwise,           20, 5, 1, 1);
  m_main_layout->addWidget(y_counterclockwise,    21, 5, 1, 1);
  m_main_layout->addWidget(z_clockwise,           20, 6, 1, 1);
  m_main_layout->addWidget(z_counterclockwise,    21, 6, 1, 1);
  m_main_layout->addWidget(scale_plus,            20, 8, 1, 1);
  m_main_layout->addWidget(scale_minus,           21, 8, 1, 1);
  m_main_layout->addWidget(fakelabel_0,           22, 0, 1, 10);
  m_main_layout->addWidget(file_select,           23, 0, 1, 3);
  m_main_layout->addWidget(bg_color_select,       23, 4, 1, 3);
  m_main_layout->addWidget(vertex_color_select,   24, 4, 1, 3);
  m_main_layout->addWidget(faces_color_select,    25, 4, 1, 3);
  m_main_layout->addWidget(vertex_type_name,      24, 0, 1, 1);
  m_main_layout->addWidget(vertex_type,           24, 1, 1, 2);
  m_main_layout->addWidget(vertex_size_name,      25, 0, 1, 1); 
  m_main_layout->addWidget(vertex_size,           25, 1, 1, 2);
  m_main_layout->addWidget(projection_type,       26, 2, 1, 1);
  m_main_layout->addWidget(dashed_face,           26, 0, 1, 2);
  m_main_layout->addWidget(line_size_name,        27, 0, 1, 1);
  m_main_layout->addWidget(line_size,             27, 1, 1, 2);


  setWindowTitle("3D_View");
}

MainWidget::~MainWidget() {
  glDisableVertexAttribArray(0);
  glDeleteBuffers(1, &m_paint_widget->VBO);
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

  delete dashed_face;

  delete projection_type;
  delete vertex_size;
  delete line_size;
  delete vertex_type;
}

void MainWidget::closeEvent(QCloseEvent *event) {
  saveSettings();
  event->accept();
}

MyButton *MainWidget::createButton(QString text) {
  MyButton *button = new MyButton(text);
  return button;
}

void MainWidget::saveSettings() {
  QString appPath = QCoreApplication::applicationDirPath();
  QSettings settings(appPath + "/config.ini", QSettings::IniFormat);
  settings.setValue("line size", m_paint_widget->preferences.l_size);
  settings.setValue("vertex size", m_paint_widget->preferences.v_size);
  settings.setValue("preferences bit", m_paint_widget->preferences.bit_bools);
  settings.setValue("background color", m_paint_widget->preferences.bg_color);
  settings.setValue("vertex color", m_paint_widget->preferences.vertex_color);
  settings.setValue("faces color", m_paint_widget->preferences.faces_color);
}

void MainWidget::readSettings() {
  QString appPath = QCoreApplication::applicationDirPath();
  QSettings settings(appPath + "/config.ini", QSettings::IniFormat);
  m_paint_widget->preferences.l_size = settings.value("line size", 1).toInt();
  m_paint_widget->preferences.v_size = settings.value("vertex size", 3).toInt();
  m_paint_widget->preferences.bit_bools =
      settings.value("preferences bit", 0).toUInt();
  m_paint_widget->preferences.bg_color =
      settings.value("background color", QColor(0, 0, 0)).value<QColor>();
  m_paint_widget->preferences.vertex_color =
      settings.value("vertex color", QColor(255, 255, 255)).value<QColor>();
  m_paint_widget->preferences.faces_color =
      settings.value("faces color", QColor(0, 255, 0)).value<QColor>();
}

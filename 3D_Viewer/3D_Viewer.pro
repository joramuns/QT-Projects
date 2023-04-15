QT += core gui printsupport opengl

macx {
  LIBS += -framework OpenGL
  QT += charts
}
unix:!macx {
  LIBS += -lGLU -lGL
}

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

SOURCES += \
        main.cpp \
        mainwidget.cpp \
        mybutton.cpp \
       paint.cpp\
        c-function/core/core.c\
        c-function/support/support_function.c

HEADERS += \
    mainwidget.h \
    mybutton.h \
    paint.h\
    c-function/core/core.h\
    c-function/support/support_function.h

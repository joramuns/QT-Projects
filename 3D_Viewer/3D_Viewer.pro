QT += core gui printsupport charts opengl

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

SOURCES += \
        main.cpp \
        mainwidget.cpp \
        mybutton.cpp \
        paint.cpp

HEADERS += \
    mainwidget.h \
    mybutton.h \
    paint.h

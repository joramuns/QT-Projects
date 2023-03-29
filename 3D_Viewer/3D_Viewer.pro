QT += core gui printsupport charts opengl

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        mybutton.cpp

HEADERS += \
    mainwindow.h \
    mybutton.h

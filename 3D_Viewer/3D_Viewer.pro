QT += core gui printsupport charts opengl

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

SOURCES += \
        genlayout.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    genlayout.h \
    mainwindow.h

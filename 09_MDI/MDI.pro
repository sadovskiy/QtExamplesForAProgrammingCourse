#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T01:25:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MDI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mdichild.cpp

HEADERS  += mainwindow.hpp \
    mdichild.h

FORMS    += mainwindow.ui

RESOURCES += \
    app.qrc

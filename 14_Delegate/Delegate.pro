QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#https://doc.qt.io/qt-5.15/modelview.html

SOURCES += main.cpp\
        mainwindow.cpp \
    spinboxdelegate.cpp \
    checkboxdelegate.cpp

HEADERS  += mainwindow.hpp \
    spinboxdelegate.hpp \
    checkboxdelegate.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
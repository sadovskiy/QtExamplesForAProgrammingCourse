# https://doc.qt.io/qt-5.15/qtwidgets-itemviews-stardelegate-example.html

QT += widgets
requires(qtConfig(tablewidget))

HEADERS       = stardelegate.h \
                stareditor.h \
                starrating.h
SOURCES       = main.cpp \
                stardelegate.cpp \
                stareditor.cpp \
                starrating.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/stardelegate
INSTALLS += target
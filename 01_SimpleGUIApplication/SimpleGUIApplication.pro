#-------------------------------------------------
#
# Project created by QtCreator 2019-03-18T14:50:02
#
#-------------------------------------------------

# Общий вид задания параметров проекта: "Параметр" "Действие" "Значение".
# Все доступные параметры и значения к ним можно посмотреть в справке Qt.
# http://doc.qt.io/qt-5/qmake-variable-reference.html
# Действия могут быть:
# Присвоить (заменить имеющиеся, если они есть) - "=";
# добавить к имеющимся - "+=";
# убрать из имеющихся - "-=";
# добавить, но только если параметр ещё не был определён - "*=".
# Значения ставятся в зависимости от параметра, например:
# TEMPLATE = app или DESTDIR = ../lib

# Подключаем модули:
# 1) ядро Qt "core";
# 2) графический интерфейс пользователя "gui".
QT += core gui

# Если версия Qt старше 4-ой, то подключать новый (qt5) модуль "widgets"
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Имя создаваемого исполняемого файла после компиляции
TARGET = SimpleGUIApplication
# Тут также можно указать путь к нему, например
# TARGET = bin/SimpleGUIApplication

# Шаблон определяет, что получится в итоге (тип программы):
# 1) приложение "app";
# 2) библиотека "lib";
# 3) руководствоваться правилами из подкаталога "subdirs";
# 4) приложение компилятора Visual Studio "vcapp";
# 5) библиотека компилятора Visual Studio "vclib";
# 6) руководствоваться правилами из подкаталога для Visual Studio "vcsubdirs".
TEMPLATE = app

# Можно добавить текущую версию программы.
# Она потом будет отображаться в свойствах
VERSION = 1.0

# Добавления флагов компилятору Си++, например pedantic
# Подробнее в справке по соответствующему компилятору.
# Например для GCC можно посмотреть тут:
# https://gcc.gnu.org/onlinedocs/gcc/Invoking-GCC.html
QMAKE_CXXFLAGS += -pedantic

# Если нужно изменить оптимизацию GCC предлагаемую по умолчанию
QMAKE_CXXFLAGS_RELEASE -= -O2 # Выключаем устанавливаемую по умолчанию оптимизацию
QMAKE_CXXFLAGS_RELEASE += -O0 # Включаем свою
# Следует отметить, что оптимизация имеет смысл только при сборке сценария релиза,
# а не отладки. По этому указан постфикс _RELEASE

# Для управления флагами связывания проекта
#QMAKE_LFLAGS += -Wl,-O2

# Внутреннее имя программы (только в Windows)
QMAKE_TARGET_PRODUCT = Example application
# Компания разработчик приложения (только в Windows)
QMAKE_TARGET_COMPANY = Private Person, Sadovskiy Boris
# Авторство и лицензия (только в Windows)
QMAKE_TARGET_COPYRIGHT = Sadovskiy Boris S., GPL

# Выдавать предупреждения компилятора для устаревших функций Qt
DEFINES += QT_DEPRECATED_WARNINGS

# Если есть желание, чтобы программа вообще не компилировалась
# в случае использования устаревших функций раскомментируйте строку
# Отключить всё API до версии Qt 6.0.0.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Кодировка исходного кода приложения для программы lupdate.
# На данный момент она уже UTF-8 по умолчанию.
# Надобность в задании этой опции отпала.
# Но на случай проблем с кодировками может пригодиться.
CODECFORSRC = UTF-8

# Поддержка стандарта Си++14
CONFIG += c++14

# Список файлов исходного кода входящих в проект
SOURCES += main.cpp \
           mainwindow.cpp

# Заголовочные файлы
HEADERS += mainwindow.hpp

# Файлы форм (на языке XML) окон приложения
FORMS += mainwindow.ui

# Файлы перевода (*.ts), которые будут рассмотрены в примере "MultiLanguage"
#TRANSLATIONS += translations/application_ru_RU.ts

# Файлы ресурсов (*.qrc), которые будут рассмотрены в примере "Menu"
#RESOURCES     = QtApplication.qrc

# Дополнительно можно указать каталоги размещения файлов, таких как
# список всех каталогов используемых в проекте;
#DEPENDPATH += . bin translations images
# каталоги размещения заголовочных файлов, как простые перечисленные через пробел,
#INCLUDEPATH += . include /usr/include/openssl
# так и с указанием платформы;
#win32:INCLUDEPATH += "C:/postgresql"
#unix:INCLUDEPATH += "/usr/include/postgresql"
# каталог расположения библиотек;
#unix:LIBS += -L/usr/local/lib -lmath
#win32:LIBS += C:/mylibs/math.lib
# каталог расположения объектных файлов (*.o) получаемых после трансляции;
#unix:OBJECTS_DIR = tmp
#win32:OBJECTS_DIR = C:/myproject/tmp
# каталог расположения файлов (moc_) получаемых после трансляции;
#unix:MOC_DIR = tmp
#win32:MOC_DIR = C:/myproject/tmp
# каталог расположения файлов (ui_) получаемых после трансляции;
#unix:UI_DIR = tmp
#win32:UI_DIR = C:/myproject/tmp
# каталог расположения файлов ресурсов (qrc_) получаемых после трансляции
#unix:RCC_DIR = tmp
#win32:RCC_DIR = C:/myproject/tmp

# Правила по умолчанию для развёртывания проекта на других платформах,
# например: qnx или android.
# Нам не понадобятся но и не мешают.
# С новой версии Qt Creator генерируются сами
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

/*
 *
 * Copyright (C) 2019 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2019 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QSettings>

/* В этой программе представленно сразу несколько вариантов,
 * которые не могут работать одновременно. Поэтому для просмотра варианта
 * надо раскоментировать его и закоментировать другой.
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Запуск метода читающего сохранённые параметры окна
    readSettings();
}

MainWindow::~MainWindow()
{
    // Запуск метода записывающего параметры окна
    writeSettings();
    delete ui;
}

void MainWindow::readSettings()
{
    QSettings settings("MySoft", "MyProgram");

    // Существует несколько способов работы с сохраняемыми параметрами
    // Первый, каждый параметр независим:
//    restoreGeometry(settings.value("geometryMainWindow").toByteArray());
    // Второй, параметры объединяются в группы:

    // Для примера сделаем группу сохраняющую параметры окна MainWindow
    settings.beginGroup("MainWindowGeometry"); // начало группы
    resize(settings.value("size", QSize(400, 400)).toSize()); // сбрасываем размеры окна
    move(settings.value("position", QPoint(200, 200)).toPoint()); // сбрасываем крайнюю левую верхнюю точку
    settings.endGroup(); // конец группы

    // и группу запоминающую состояние компонента CheckBox
    settings.beginGroup("MainWindowCheckBox");

    // Так как у нас состояние CheckBox описано с помощью enum,
    // а в файл скидывается целое число то надо либо с помощью switch
    // расставлять значения
//    switch (settings.value("CheckState", Qt::Unchecked).toInt()) {
//    case Qt::Unchecked:
//        ui->checkBox->setCheckState(Qt::Unchecked);
//        break;
//    case Qt::PartiallyChecked:
//        ui->checkBox->setCheckState(Qt::PartiallyChecked);
//        break;
//    case Qt::Checked:
//        ui->checkBox->setCheckState(Qt::Checked);
//        break;
//    }
    // либо (что более компактно) просто передать целое,
    // которое соответствует константе enum с приведением типа к Qt::CheckState
//    ui->checkBox->setCheckState((Qt::CheckState)settings.value("CheckState",
//                                                               Qt::Unchecked).toInt());
    // или ещё вариант с привидением типа в стиле Си++
    ui->checkBox->setCheckState(static_cast<Qt::CheckState>(settings.value("CheckState",
                                                               Qt::Unchecked).toInt()));
    settings.endGroup();
}

void MainWindow::writeSettings()
{
    QSettings settings("MySoft", "MyProgram");

    // Запись значений также как и чтение либо по одному, либо по группам
    // Пример по одному:
//    settings.setValue("geometryMainWindow", saveGeometry());
    // Пример по группам MainWindowGeometry и MainWindowCheckBox:
    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.endGroup();

    settings.beginGroup("MainWindowCheckBox");
    settings.setValue("CheckState", ui->checkBox->checkState());
    settings.endGroup();
}

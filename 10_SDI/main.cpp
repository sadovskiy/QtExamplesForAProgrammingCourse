/*
 *
 * Copyright (C) 2016 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2016 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /**
     * Для создания окон больше одного,
     * их надо создавать с динамической продолжительностю хранения
     */
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();

    return app.exec();
}

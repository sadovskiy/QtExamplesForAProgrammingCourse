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

/*
 * Подключение главной библиотеки.
 * Объект её класса является ядром (с поддержкой GUI) нашего приложения
 */
#include <QApplication>

int main(int argc, char *argv[])
{
    // Создаём ядро (с поддержкой GUI) приложения с названием объекта "app"
    QApplication app(argc, argv);
    // Создаём главное окно с названием объекта "mainWindow"
    MainWindow mainWindow;

    // Отобразить главное окно на экране (по умолчанию оно скрыто)
    mainWindow.show();

    /*
     * Перевести приложение в режим ожидания действий пользователя
     * Внутри находится основной цикл событий ожидающий вызова "exit()"
     * для выхода из приложения.
     * Как правило никакое взаимодействие с пользователем приложения
     * не может быть до вызова этого метода
     */
    return app.exec();
}

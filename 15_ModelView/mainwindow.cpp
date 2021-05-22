/*
 *
 * Copyright (C) 2021 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2021 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

// Подробно реализация механизма Модель-Представление-Контроллер описана в документации,
// например тут: https://doc.qt.io/qt-5/modelview.html
// и тут: https://ru.wikipedia.org/wiki/Model-View-Controller

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "tablemodel.hpp"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    // Выделяем память под создаваемую модель данных
    , tableModel(new TableModel(this))
{
    ui->setupUi(this);

    // Для вставки в таблицу данных связываем сигнал нажатия на кнопку
    // со слотом, который вставит данные в модель
    connect(ui->pushButtonAddString, &QPushButton::clicked,
            this, &MainWindow::insertValueToTable);

    // Задаём представлению (View) модель данных, которую оно будет отображать
    ui->tableView->setModel(tableModel);
}

MainWindow::~MainWindow()
{
    delete tableModel;
    delete ui;
}

void MainWindow::insertValueToTable()
{
    // На всякий случай лучше проверить на существование в памяти модели
    if (tableModel)
        // И если модель существует, то вставляем текст
        // из поля ввода lineEdit в нашу модель tableModel
        tableModel->insertValue(ui->lineEdit->text());
}


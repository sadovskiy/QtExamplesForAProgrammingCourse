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

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMimeData>
#include <QList>
#include <QStringList>

#include "mytablewidget.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Для возможности перетаскивания важно установить тип MIME.
    // От этого зависит как приложения (включая наше) смогут воспринимать
    // перенесённый в них объект.
    // Для демонстрации важности установки этого типа вытащим доступные значения
    // определённые в нашей таблице и запишем их в выпадающий спискок,
    // что бы пользователь мог во время работы приложения менять типы MIME
    ui->comboBoxMimeTypeCustomTable->addItems(
                ui->tableWidgetDagAndDropCustom->model()->mimeTypes());

    connect(ui->tableWidgetDagAndDropCustom, &MyTableWidget::enableDelimiterChange,
            [=](bool state)
    {
        ui->comboBoxColumnDelimiterCustomTable->setEnabled(state);
        ui->comboBoxRowDelimiterCustomTable->setEnabled(state);
        ui->comboBoxColumnDelimiterCustomTable->setCurrentIndex(0);
        ui->comboBoxRowDelimiterCustomTable->setCurrentIndex(0);
    });

    // Установим связь сигнала выбора пользователем типа MIME со слотом
    // устанавливающим в качестве основного выбраны тип
    connect(ui->comboBoxMimeTypeCustomTable, &QComboBox::currentTextChanged,
            ui->tableWidgetDagAndDropCustom, &MyTableWidget::setMimeType);

    connect(ui->comboBoxColumnDelimiterCustomTable, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->tableWidgetDagAndDropCustom, &MyTableWidget::setColumnDelimiter);
    connect(ui->comboBoxRowDelimiterCustomTable, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->tableWidgetDagAndDropCustom, &MyTableWidget::setRowDelimiter);

    connect(ui->checkBoxQuotesMark, &QCheckBox::clicked,
            ui->tableWidgetDagAndDropCustom, &MyTableWidget::setQuotes);
}

MainWindow::~MainWindow()
{
    delete ui;
}


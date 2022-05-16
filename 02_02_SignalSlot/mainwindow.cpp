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
#include "timer.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , myTimer(new Timer(this)) // Выделяем на таймер память.
{
    ui->setupUi(this);

    /*
     * Соединение созданного нами сигнала "step(int)"
     * и созданного нами слота "setValue(int)"
     * Так как сигнал "step(int)" созданн в классе "Timer",
     * то пишем объект этого класса "myTimer".
     * В свою очередь слот "setValue(int)" создан в этом же классе
     * и по этому для него используем указатель "this".
     */
    // Старый вариант
//    connect(myTimer, SIGNAL(step(int)), this, SLOT(setValue(int)));
    // Новый вариант
//    connect(myTimer, &Timer::step, this, &MainWindow::setValue);
    // или напрямую в progressBar без вызова мтода-слота (также в новом синтаксисе)
     connect(myTimer, &Timer::step, ui->progressBar, &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    delete myTimer; // Удаляем наш динамический объект.
    delete ui;
}

void MainWindow::setValue(const int value)
{
    // Задаём новое значение на визуальный компонент "progressBar".
    ui->progressBar->setValue(value);
}

void MainWindow::on_pushButtonStart_clicked()
{
    /*
     * Запускаем таймер вызовом метода "start(int count, int ms)",
     * где "count" - это количество операций,
     * а "ms" - это задержка в миллисекундах.
     */
    myTimer->start(100, 5000);
    // В данном методе, будет испускаться сигнал со значением "count"
    // и периодичностью ms и передавать значение в слот "setValue(int value)".
}

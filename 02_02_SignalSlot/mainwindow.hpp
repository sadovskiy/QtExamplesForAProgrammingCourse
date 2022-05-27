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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

// Сделаем предварительное объявление для нашего класса таймера "Timer".
class Timer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слот, вызываемый на сигнал "step(int value)" класса "Timer".
    void setValue(const int value);

    void on_pushButtonStart_clicked();

private:
    Ui::MainWindow *ui;
    Timer *myTimer; // Создадим указатель типа Timer.
};

#endif // MAINWINDOW_HPP

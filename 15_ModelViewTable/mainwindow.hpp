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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слот, который будет добавлять значение в таблицу
    void insertValueToTable();

private:
    Ui::MainWindow *ui;
    TableModel *tableModel; // Указатель на нашу модель
};
#endif // MAINWINDOW_HPP

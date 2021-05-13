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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слот, созданный в Qt Designer, через пункт меню "Перейти к слоту..."
    void on_pushButtonSecondary_clicked(bool checked);
    // Слот, созданный нами (вручную)
    void setTextInLabel();

    // Слот, созданный нами (вручную) для демонстрации перегрузки сигналов
    void setValue(const int value);

    // Слот, созданный в Qt Designer, через пункт меню "Перейти к слоту..."
    void on_actionLineEditTextChenged_triggered(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP

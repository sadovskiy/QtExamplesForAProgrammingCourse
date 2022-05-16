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

#include "formwindow.hpp"

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
    void on_buttonDialogWindowA_clicked();

    void on_pushButtonFormWindowA_clicked();

    void setStatusBarMessage(const FormWindow::UserData ud);

    void on_buttonNewWindowD_clicked();

    void on_buttonExistingWindowD_clicked();

private:
    Ui::MainWindow *ui;
    FormWindow autoGlobWindow;
    FormWindow *dynamicWndow;

    FormWindow::UserData mUserData;
};

#endif // MAINWINDOW_HPP

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
#include <QPointer>

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
    // Реализация слотов реализующих отработку нажатия на соответствующие кнопки
    void on_buttonDialogWindowA_clicked();
    void on_buttonFormWindowA_clicked();
    void on_buttonNewWindowD_clicked();
    void on_buttonExistingWindowD_clicked();
    void on_buttonNewWindowP_clicked();
    void on_buttonExistingWindowP_clicked();
    void on_buttonDeleteP_clicked();
    void on_buttonDeleteD_clicked();

    // Слот реализующий размещение текста в нижней части окна
    void setStatusBarMessage(const FormWindow::UserData &ud);

private:
    Ui::MainWindow *ui;
    // Окно с автоматической продолжительностью хранения,
    // но за счёт объявления в классе будет существовать пока не будет удалён
    // объект этого класса с доступом из любого метода этого класса.
    FormWindow autoGlobWindow;
    // Вариант создания окна с динамической продолжительностью хранения
    FormWindow *dynamicWndowD;
    // Другой вариант создания динамического окна через класс QPointer
    QPointer<FormWindow> dynamicWndowP;

    // Переменные подсчёта созданных окон. Помогают вести учёт,
    // сколько окон было создано
    int windowCountD;
    int windowCountP;

    // Набор данные о пользователе (логин и пароль)
    FormWindow::UserData mUserData;
};

#endif // MAINWINDOW_HPP

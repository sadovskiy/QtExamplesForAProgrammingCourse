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

class QActionGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слот реализует реакцию на нажатие по любому
    // пункту меню входящему в группу sizePolicyActionGroup
    void setSizePolicy(QAction *action);

    // Слоты сработают на нажатие по переключателю
    // типа QRadioButton
    void on_radioButtonList1_clicked(bool checked);
    void on_radioButtonList2_clicked(bool checked);
    // Слот сработает на изменение значений объекта spinBox
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    // Создаём группу из пунктов меню типа QAction
    QActionGroup *sizePolicyActionGroup;
};

#endif // MAINWINDOW_HPP

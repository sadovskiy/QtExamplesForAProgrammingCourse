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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Соединение сигнала нажатия на кнопку и слота класса "MainWindow"
    connect(ui->pushButtonPrimary, &QPushButton::clicked,
            this, &MainWindow::setTextInLabel);
    /* где
     * "ui->pushButtonPrimary" - объект, который испускает сигнал.
     * "clicked()" - сигнал, испускаемый при нажатии на кнопку.
     * "this" - объект, где располагается слот.
     * "setTextInLabel()" - слот, который предназначен для обработки сигнала.
     */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSecondary_clicked(bool checked)
{
    /*
     * Если кнопка "pushButtonSecondary" нажата,
     * то включается связь сигнала перемещения "horizontalSlider"
     * со слотом установки значения "progressBarSecondary"
     */
    if (checked)
        connect(ui->horizontalSlider, &QSlider::valueChanged,
                ui->progressBarSecondary, &QProgressBar::setValue);
    // В противном случае разорвать связь
    else
        disconnect(ui->horizontalSlider, &QSlider::valueChanged,
                   ui->progressBarSecondary, &QProgressBar::setValue);
}

// Слот будет вызываться при нажатии на кнопку "pushButtonPrimary"
void MainWindow::setTextInLabel()
{
    // Записываем текст из поля ввода в метку.
    //    QString str = ui->lineEdit->text();
    //    ui->label->setText(str);

    // Или более короткий вариант того же самого
    // без использования временной переменной.
    ui->label->setText(ui->lineEdit->text());
}

void MainWindow::on_actionLineEditTextChenged_triggered(bool checked)
{
    // Аналогично описанию выше для кнопки,
    // но тут сигнал испускается при редактировании
    // текста в поле "lineEdit"
    if (checked)
        connect(ui->lineEdit, &QLineEdit::textChanged,
                ui->label, &QLabel::setText);
    else
        disconnect(ui->lineEdit, &QLineEdit::textChanged,
                   ui->label, &QLabel::setText);

}

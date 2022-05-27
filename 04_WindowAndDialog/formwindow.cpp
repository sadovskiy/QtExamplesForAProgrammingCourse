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

#include "formwindow.hpp"
#include "ui_formwindow.h"

FormWindow::FormWindow(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::FormWindow)
{
    // Следует помнить, все обращения к объектам на форме через указатель ui
    // должны быть после вызова этого метода
    ui->setupUi(this);
}

FormWindow::~FormWindow()
{
    delete ui;
}

void FormWindow::setUserData(const UserData& ud)
{
    // Возможны два варианта работы с составными переменными
    // почленное копирование
//    currentData.userName = ud.userName;
//    currentData.password = ud.password;
    // или более компактно копирование всего объекта
    currentData = ud;
}

FormWindow::UserData FormWindow::userData() const
{
    return currentData;
}

void FormWindow::currentDataToLineEditFild()
{
    ui->lineEditUserName->setText(currentData.userName);
    ui->lineEditPassword->setText(currentData.password);
}

// Реализация метода работающего при нажатии пользователя на кнопку OK
void FormWindow::on_pushButtonOK_clicked()
{
    // Тут поскольку данные надо скопировать из разные объектов
    // возможно использование только почленного копирования
    currentData.userName = ui->lineEditUserName->text();
    currentData.password = ui->lineEditPassword->text();

    // После копирования можно испустить сигнал с передачей новых данных
    emit valueChanged(currentData);

    // Закрываем окно
    close();
}

// Реализация метода работающего при нажатии пользователя на кнопку Cancel
void FormWindow::on_pushButtonCancel_clicked()
{
    // Просто закрываем окно
    close();
}

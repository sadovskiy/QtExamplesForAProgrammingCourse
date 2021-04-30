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
    ui->setupUi(this);
}

FormWindow::~FormWindow()
{
    delete ui;
}

void FormWindow::setUserDataWin(const UserData& ud)
{
//    currentData.userName = ud.userName;
//    currentData.password = ud.password;
    // или
    currentData = ud;
}

FormWindow::UserData FormWindow::userDataWin() const
{
    return currentData;
}


void FormWindow::on_pushButtonOK_clicked()
{
    currentData.userName = ui->lineEditUserName->text();
    currentData.password = ui->lineEditPassword->text();

    emit valueChanged(currentData);

    close();
}

void FormWindow::on_pushButtonCancel_clicked()
{
    close();
}

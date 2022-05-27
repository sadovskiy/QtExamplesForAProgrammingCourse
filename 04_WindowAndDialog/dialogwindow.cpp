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

#include "dialogwindow.hpp"
#include "ui_dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent) :
    QDialog(parent)
  , ui(new Ui::DialogWindow)
{
    // Следует помнить, все обращения к объектам на форме через указатель ui
    // должны быть после вызова этого метода
    ui->setupUi(this);
}

DialogWindow::~DialogWindow()
{
    delete ui;
}

// Реализация метода отправляющего данные в объет ui->lineEdit
void DialogWindow::setData(const QString &str)
{
    // Записываем текст из переменной str в объект ui->lineEdit
    ui->lineEdit->setText(str);
}

// Реализация метода получающего данные из объекта ui->lineEdit
QString DialogWindow::data() const
{
    return ui->lineEdit->text();
}

// Слот срабатывающий при редактировании текста в компоненте ui->lineEdit,
// будет получать новое содержимое строки через аргумент arg1
void DialogWindow::on_lineEdit_textChanged(const QString &arg1)
{
    // Проверяем есть ли в нём вообще какие-нибудь данные
    if (!arg1.isEmpty()) {
        // Если данные есть, то скопируем из в переменную mStr
        mStr = arg1;
        // и включим кнопку OK
        ui->pushButtonOK->setEnabled(true);
    }
    else
        // Если данные нет, то выключим кнопку ОК
        ui->pushButtonOK->setDisabled(true);
    // Таким образом пользователь сможет нажать на неё, только если в поле
    // ui->lineEdit будут какие-либо данные
}

/* *
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
#include "dialogwindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , autoGlobWindow(this)
  , dynamicWndow(nullptr)
{
    ui->setupUi(this);
    autoGlobWindow.setWindowFlag(Qt::Window);
    connect(&autoGlobWindow, &FormWindow::valueChanged,
            this, &MainWindow::setStatusBarMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonDialogWindowA_clicked()
{
    DialogWindow dialog(this);

    dialog.exec();

    if (dialog.result() == DialogWindow::Accepted)
        ui->statusBar->showMessage(dialog.string());
}

void MainWindow::on_pushButtonFormWindowA_clicked()
{
    FormWindow::UserData ud = {"test", "test"};
    autoGlobWindow.setUserDataWin(ud);
    autoGlobWindow.show();
}

void MainWindow::setStatusBarMessage(FormWindow::UserData ud)
{
    ui->statusBar->showMessage("User Name: " + ud.userName + \
                               " |Password: " + ud.password,
                               5000);
}

void MainWindow::on_buttonNewWindowD_clicked()
{

    dynamicWndow = new FormWindow(this);
    dynamicWndow->setWindowFlag(Qt::Window);
    if (ui->checkBoxModal->checkState() == Qt::Checked)
        dynamicWndow->setWindowModality(Qt::WindowModal);
    dynamicWndow->show();
    //    dynamicWndow->setAttribute(Qt::WA_DeleteOnClose);
    //    connect(dynamicWndow, &FormWindow::valueChanged,
    //            this, &MainWindow::setStatusBarMessage);


}

void MainWindow::on_buttonExistingWindowD_clicked()
{
    dynamicWndow->show();
}

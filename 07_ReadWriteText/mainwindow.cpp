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

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QListWidget>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 2);
    connect(ui->listWidget, &QListWidget::itemClicked,
            this, &MainWindow::clickedItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePathAndName = QFileDialog::getOpenFileName(this);
    if (!filePathAndName.isEmpty())
        loadFile(filePathAndName);
}

void MainWindow::on_actionSave_triggered()
{
    QString filePathAndName = QFileDialog::getSaveFileName(this);
    if (!filePathAndName.isEmpty())
        saveFile(filePathAndName);
}

void MainWindow::clickedItem(QListWidgetItem *item)
{
    item->setFlags(item->flags () | Qt::ItemIsEditable);
}

void MainWindow::loadFile(const QString &filePathAndName)
{
    QFile file(filePathAndName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(filePathAndName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);

    if (ui->radioButtonTE->isChecked()) {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui->textEdit->setPlainText(in.readAll());
        QApplication::restoreOverrideCursor();
    }

    if (ui->radioButtonLW->isChecked()) {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        while (!in.atEnd()) {
            ui->listWidget->addItem(in.readLine());
        }
        QApplication::restoreOverrideCursor();
    }
    ui->label->setText(QFileInfo(filePathAndName).fileName());
}

void MainWindow::saveFile(const QString &filePathAndName)
{
    QFile file(filePathAndName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(filePathAndName).arg(file.errorString()));
        return;
    }

    QTextStream out(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    if (ui->radioButtonTE->isChecked()) {
        out << ui->textEdit->toPlainText();
    }

    if (ui->radioButtonLW->isChecked()) {
        int c = ui->listWidget->count();
        for (int var = 0; var < c; ++var) {
            out << ui->listWidget->item(var)->text() + "\n";
        }
    }
    QApplication::restoreOverrideCursor();
    ui->label->setText(QFileInfo(filePathAndName).fileName());
}

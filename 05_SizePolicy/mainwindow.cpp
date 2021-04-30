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
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sizePolicyActionGroup(new QActionGroup(this))
{
    ui->setupUi(this);

    ui->actionFixed->setData(QSizePolicy::Fixed);
    sizePolicyActionGroup->addAction(ui->actionFixed);

    ui->actionMinimum->setData(QSizePolicy::Minimum);
    sizePolicyActionGroup->addAction(ui->actionMinimum);

    ui->actionMaximum->setData(QSizePolicy::Maximum);
    sizePolicyActionGroup->addAction(ui->actionMaximum);

    ui->actionPreferred->setData(QSizePolicy::Preferred);
    sizePolicyActionGroup->addAction(ui->actionPreferred);

    ui->actionExpanding->setData(QSizePolicy::Expanding);
    sizePolicyActionGroup->addAction(ui->actionExpanding);

    ui->actionMinimumExpanding->setData(QSizePolicy::MinimumExpanding);
    sizePolicyActionGroup->addAction(ui->actionMinimumExpanding);

    ui->actionIgnored->setData(QSizePolicy::Ignored);
    sizePolicyActionGroup->addAction(ui->actionIgnored);

    connect(sizePolicyActionGroup, &QActionGroup::triggered,
            this, &MainWindow::setSizePolicy);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSizePolicy(QAction *action)
{
    if (ui->radioButtonList1->isChecked())
        switch (action->data().toInt()) {
        case QSizePolicy::Fixed:
            ui->listWidget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            break;
        case QSizePolicy::Minimum:
            ui->listWidget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
            break;
        case QSizePolicy::Maximum:
            ui->listWidget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
            break;
        case QSizePolicy::Preferred:
            ui->listWidget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            break;
        case QSizePolicy::Expanding:
            ui->listWidget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            break;
        case QSizePolicy::MinimumExpanding:
            ui->listWidget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
            break;
        case QSizePolicy::Ignored:
            ui->listWidget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
            break;
        }
    if (ui->radioButtonList2->isChecked())
        switch (action->data().toInt()) {
        case QSizePolicy::Fixed:
            ui->listWidget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            break;
        case QSizePolicy::Minimum:
            ui->listWidget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
            break;
        case QSizePolicy::Maximum:
            ui->listWidget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
            break;
        case QSizePolicy::Preferred:
            ui->listWidget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            break;
        case QSizePolicy::Expanding:
            ui->listWidget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            break;
        case QSizePolicy::MinimumExpanding:
            ui->listWidget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
            break;
        case QSizePolicy::Ignored:
            ui->listWidget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
            break;
        }
}

void MainWindow::on_radioButtonList1_clicked(bool checked)
{
    if (checked) {
        switch (ui->listWidget1->sizePolicy().verticalPolicy()) {
        case QSizePolicy::Fixed:
            ui->actionFixed->setChecked(true);
            break;
        case QSizePolicy::Minimum:
            ui->actionMinimum->setChecked(true);
            break;
        case QSizePolicy::Maximum:
            ui->actionMaximum->setChecked(true);
            break;
        case QSizePolicy::Preferred:
            ui->actionPreferred->setChecked(true);
            break;
        case QSizePolicy::Expanding:
            ui->actionExpanding->setChecked(true);
            break;
        case QSizePolicy::MinimumExpanding:
            ui->actionMinimumExpanding->setChecked(true);
            break;
        case QSizePolicy::Ignored:
            ui->actionIgnored->setChecked(true);
            break;
        }
        ui->spinBox->setValue(ui->verticalLayout_3->stretch(1));
    }
}

void MainWindow::on_radioButtonList2_clicked(bool checked)
{
    if (checked){
        switch (ui->listWidget2->sizePolicy().verticalPolicy()) {
        case QSizePolicy::Fixed:
            ui->actionFixed->setChecked(true);
            break;
        case QSizePolicy::Minimum:
            ui->actionMinimum->setChecked(true);
            break;
        case QSizePolicy::Maximum:
            ui->actionMaximum->setChecked(true);
            break;
        case QSizePolicy::Preferred:
            ui->actionPreferred->setChecked(true);
            break;
        case QSizePolicy::Expanding:
            ui->actionExpanding->setChecked(true);
            break;
        case QSizePolicy::MinimumExpanding:
            ui->actionMinimumExpanding->setChecked(true);
            break;
        case QSizePolicy::Ignored:
            ui->actionIgnored->setChecked(true);
            break;
        }
        ui->spinBox->setValue(ui->verticalLayout_3->stretch(2));
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (ui->radioButtonList1->isChecked())
        ui->verticalLayout_3->setStretch(1, arg1);

    if (ui->radioButtonList2->isChecked())
        ui->verticalLayout_3->setStretch(2, arg1);
}

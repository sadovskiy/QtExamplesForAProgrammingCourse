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
    // Следует помнить, все обращения к объектам на форме через указатель ui
    // должны быть после вызова этого метода
    ui->setupUi(this);

    // У каждого пункта меню есть специальное поле данных.
    // Туда можно прятать различные значения.
    // Нам удобно сложить туда идентификаторы соответствующих им политик
    ui->actionFixed->setData(QSizePolicy::Fixed);
    ui->actionMinimum->setData(QSizePolicy::Minimum);
    ui->actionMaximum->setData(QSizePolicy::Maximum);
    ui->actionPreferred->setData(QSizePolicy::Preferred);
    ui->actionExpanding->setData(QSizePolicy::Expanding);
    ui->actionMinimumExpanding->setData(QSizePolicy::MinimumExpanding);
    ui->actionIgnored->setData(QSizePolicy::Ignored);

    // Добавим пункты меню в общую группу
    sizePolicyActionGroup->addAction(ui->actionFixed);
    sizePolicyActionGroup->addAction(ui->actionMinimum);
    sizePolicyActionGroup->addAction(ui->actionMaximum);
    sizePolicyActionGroup->addAction(ui->actionPreferred);
    sizePolicyActionGroup->addAction(ui->actionExpanding);
    sizePolicyActionGroup->addAction(ui->actionMinimumExpanding);
    sizePolicyActionGroup->addAction(ui->actionIgnored);

    // Подсоединим к сигналу triggered группы sizePolicyActionGroup
    // слот setSizePolicy
    connect(sizePolicyActionGroup, &QActionGroup::triggered,
            this, &MainWindow::setSizePolicy);

    // Определим выбор пользователя по умолчанию, на момент запуска
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
    case QSizePolicy::MinimumExpanding:
        ui->actionMinimumExpanding->setChecked(true);
        break;
    case QSizePolicy::Expanding:
        ui->actionExpanding->setChecked(true);
        break;
    case QSizePolicy::Ignored:
        ui->actionIgnored->setChecked(true);
        break;
    }
    //  или тоже самое но короче
//    if (ui->listWidget1->sizePolicy().verticalPolicy() ==
//            QSizePolicy::Fixed)
//        ui->actionFixed->setChecked(true);
    // Само значение по умолчанию, проставлено в форме окна MainWindow
    // через дизайнер Qt
}

MainWindow::~MainWindow()
{
    // Удаляем группу, когда окно будет закрываться
    delete sizePolicyActionGroup;
    delete ui;
}

// Данный метод при срабатывании получает указатель на пункт меню
// по которому было нажато пользователем
void MainWindow::setSizePolicy(QAction *action)
{
    // Проверяем, в каком положении находится переключатель
    // Если он установлен на radioButtonList1,
    if (ui->radioButtonList1->isChecked())
        // то выясняем какой пункт меню был выбран пользователем
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
    // Аналогично действию выше
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
    // или более коротки вариант
//    ui->listWidget1->setSizePolicy(QSizePolicy::Fixed,
//                                   (QSizePolicy::Policy)action->data().toInt());
}

// Слот обработки нажатия пользователя по переключателю radioButtonList1
void MainWindow::on_radioButtonList1_clicked(bool checked)
{
    // Если было нажатие на этот переключатель,
    if (checked) {
        // то выясняем какая политика действует в элементе listWidget1
        // в данный момент и отмечаем соответствующий пункт меню.
        // Это нужно, что бы при переключении между
        // radioButtonList1 и radioButtonList2, пункты меню политик по вертикали
        // выставлялись в соответствии с их фактическими значениями
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
        // Передаём текущую пропорцию между объектами listWidget1 и listWidget2
        // полю ввода spinBox
        ui->spinBox->setValue(ui->verticalLayoutMainWindow->stretch(1));
    }
}

void MainWindow::on_radioButtonList2_clicked(bool checked)
{
    // Тут всё аналогично предыдущему методу
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
        ui->spinBox->setValue(ui->verticalLayoutMainWindow->stretch(2));
    }
}

// Метод срабатывающий на изменение значений в поле ввода spinBox
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    // Получаем через формальный параметр arg1 значение, введённое
    // пользователем и после определения в каком положении находится
    // переключатель типа QRadioButton, выставляем значение
    if (ui->radioButtonList1->isChecked())
        // пропорции занимаемой области объектом listWidget1
        ui->verticalLayoutMainWindow->setStretch(1, arg1);
    // Первый аргумент в методе setStretch(1, arg1) - это
    // порядковый номер объекта listWidget1 на форме MainWindow

    if (ui->radioButtonList2->isChecked())
        // и listWidget2
        ui->verticalLayoutMainWindow->setStretch(2, arg1);
    // Первый аргумент в методе setStretch(2, arg1) - это
    // порядковый номер объекта listWidget2 на форме MainWindow
}

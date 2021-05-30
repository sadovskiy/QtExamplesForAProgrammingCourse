/*
 *
 * Copyright (C) 2021 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2021 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

// Подробно работа с делегатами (Контроллерами) описана в документации,
// например тут: https://doc.qt.io/qt-5/modelview.html
// раздел 3.4 Delegates.

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "spinboxdelegate.hpp"
#include "checkboxdelegate.hpp"
#include "comboboxdelegate.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  ,  ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Если слот или сигнал перегружен,
    // то придётся использовать специальный синтаксис.
    // Про это подробно было в примере 02_01_SignalSlot,
    // а тут рассмотрен пример для более сложных чем int аргументов.
    // Что бы использовать вариант для С++11 надо просто раскомментировать
    // две строки ниже
//    connect(ui->tableWidget, &QTableWidget::activated,
//            ui->tableWidget, QOverload<const QModelIndex &>::of(&QTableWidget::edit));

    // Что бы использовать другой вариант надо включить
    // в файле конфига "Delegate.pro" поддержку С++14
    // и раскомментировать две строки ниже, а верхний connect() закомментировать
//    connect(ui->tableWidget, &QTableWidget::activated,
//            ui->tableWidget, qOverload<const QModelIndex &>(&QTableWidget::edit));


    // В один момент времени должен работать только какой-нибудь один вариант.
    // Оба варианта связывают нажатие указателем мыши на ячейку таблицы
    // с открытием формы редактирования. Можно использовать если надо,
    // чтобы ячейка сразу открывалась на редактирование, а не выделялась


    // Создать делегат (форма обработки данных)
    // по обработке ввода данных в ячейку, использующий QSpinBox
    SpinBoxDelegate *spDelegate = new SpinBoxDelegate(this);

    // Установить для первого столбца в качестве ячейки ввода
    // нашу ячейку delegate с элементом ввода QSpinBox
    ui->tableWidget->setItemDelegateForColumn(0, spDelegate);

    // Два оператора выше можно записать в один оператор
//    ui->tableWidget->setItemDelegateForColumn(0, new SpinBoxDelegate(this));

    // То же самое для элемента QCheckBox и сразу запишем в один оператор
    ui->tableWidget->setItemDelegateForColumn(1, new CheckBoxDelegate(this));

    // После добавления можно выровнять толщину столбцов
    // по значению самого широкого
    ui->tableWidget->resizeColumnToContents(1);

    // Если содержимое таблицы меньше по ширине чем размер окна,
    // то за последним столбцом будет пустое пространство.
    // Если хотите, что бы его не было, то можно растянуть последний
    // столбец до конца таблицы
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ComboBoxDelegate *cbDelegate = new ComboBoxDelegate(this);

    cbDelegate->setData(QStringList({ "Hello", "my", "world!" }));

    ui->tableWidget->setItemDelegateForColumn(2, cbDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

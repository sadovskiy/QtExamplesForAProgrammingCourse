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

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDebug>

#include "device.hpp"

// Зададим базовый набор констант для нашего примера
#define ROW_COUNT 0
#define COLUMN_COUNT 2
#define COLUMN_MANUFACTURER 0
#define COLUMN_MODEL 1

// Функция инициализации таблицы
// В реальных приложениях вместо неё идёт загрузка
// данных из файла, БД, сайта и т.д.
void MainWindow::init()
{
    int row = 0;

    // Создадим данные для контрольного примера
    devList.addDevice(Device(row, "Intel", "Core i9-10980XE"));
    devList.addDevice(Device(++row, "AMD", "EPYC 7452"));
    devList.addDevice(Device(++row, "Intel", "Core i5-10400F"));
    devList.addDevice(Device(++row, "Intel", "Core i3-10100F"));
    devList.addDevice(Device(++row, "AMD", "Ryzen 5 PRO 4650G"));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , rowCount(ROW_COUNT)
    , columnCount(COLUMN_COUNT)
{
    ui->setupUi(this);

    // Загрузим данные в таблицу
    init();

    // Узнаем сколько строк на данный момент в контейнере devList
    rowCount = devList.count();

    // Задаём размер таблицы
    ui->tableWidget->setColumnCount(columnCount);
    ui->tableWidget->setRowCount(rowCount);

    // Задаём заголовки столбцов таблицы
    ui->tableWidget->setHorizontalHeaderLabels(QStringList({"Manufacturer", "Model"}));

    // Заполняем таблицу данными из контейнера devList
    for (int row = 0; row < rowCount; ++row) {
        ui->tableWidget->setItem(row,
                                 COLUMN_MANUFACTURER,
                                 new QTableWidgetItem(
                                     QString::fromStdString(
                                         devList.findDevice(row)->manufacturer())));
        ui->tableWidget->setItem(row,
                                 COLUMN_MODEL,
                                 new QTableWidgetItem(
                                     QString::fromStdString(
                                         devList.findDevice(row)->model())));
    }

    // По умолчанию, все столбцы имеют одинаковый средний размер,
    // что часто бывает некрасиво и скрывает часть данных.
    // По этому после загрузки данных, можно выставить размер колонки
    // индивидуально свой по самой длинной записи в строке
    ui->tableWidget->resizeColumnsToContents();

    // Сделаем связь между сигналом редактирования ячейки и слотом,
    // который вытаскивает новые данные из этой ячейки и передаёт из неё в контейнер
    connect(ui->tableWidget, &QTableWidget::itemChanged,
            this, &MainWindow::itemChanged);
    // Связь между сигналом изменения порядка сортировки и слотом переключающим
    // радиокнопки панели Sort Order
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sortIndicatorChanged,
            this, &MainWindow::sortHeader);

    // Сделаем активную ячейку по умолчанию
    ui->tableWidget->setCurrentCell(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButtonSortAscending_released()
{
    // Сортируем выделенный столбец по возрастанию
    ui->tableWidget->sortByColumn(ui->tableWidget->currentColumn(),
                                  Qt::AscendingOrder);
    // Следует заметить, что это работает только внутри объекта ui->tableWidget
}

void MainWindow::on_radioButtonSortDescending_released()
{
    // Сортируем выделенный столбец по убыванию
    ui->tableWidget->sortByColumn(ui->tableWidget->currentColumn(),
                                  Qt::DescendingOrder);
    // Следует заметить, что это работает только внутри объекта ui->tableWidget
}

void MainWindow::on_pushButtonOutput_clicked()
{
    // Выводим содержимое контейнера devList в консоль
    for (int row = 0; row < rowCount; ++row)
        // Поскольку методы класса Device возвращают в типе std::string,
        // то для вывода нужно сделать перевод в тип QString
        qDebug() << QString::fromStdString(devList.findDevice(row)->manufacturer())
                 << QString::fromStdString(devList.findDevice(row)->model());

    ui->tableWidget->item(0, COLUMN_MANUFACTURER)->setSelected(true);
}

// Метод переносит изменённые данные из ячейки таблицы в объект
// типа Device контейнера devList
void MainWindow::itemChanged(QTableWidgetItem *item)
{
    // Определяем в каком столбце были изменения
    switch (item->column()) {
    case COLUMN_MANUFACTURER:
        // Перенос данных записанный в одну строку, подробнее можно расписать так:
        // например вторую
        // 1. int r = item->row();
        // указатель на найденный элемент
        // 2. Device *dev = devList.findDevice(item->row());
        // получаем данные из ячейки
        // 3. QVariant data = item->data(Qt::DisplayRole);
        // получаем строку типа QString из данных типа QVariant
        // 4. QString qstr = data.toString();
        // получаем строку типа std::string из строки типа QString
        // 5. std::string str = qstr.toStdString();
        // вставляем новые данные в элемент типа Device по указателю dev
        // 6. dev->setManufacturer(str);
        devList.findDevice(item->row())->setManufacturer(
                    item->data(Qt::DisplayRole).toString().toStdString());
        break;
    case COLUMN_MODEL:
        // Аналогично предыдущему варианту
        devList.findDevice(item->row())->setModel(
                    item->data(Qt::DisplayRole).toString().toStdString());
        break;
    default:
        return;
    }
}

// Метод переключает кнопки порядка сортировки
void MainWindow::sortHeader(int logicalIndex, Qt::SortOrder order)
{
    // В качестве аргумента получаем, в каком порядке сортировать данные.
    // Это определяет флажок направления сортировки в заголовке столбца,
    // по которому нажимает пользователь
    switch (order) {
    case Qt::AscendingOrder:
        ui->radioButtonSortAscending->setChecked(true);
        break;
    case Qt::DescendingOrder:
        ui->radioButtonSortDescending->setChecked(true);
        break;
    }

    // Выделяем колонку по которой была сортировка
    ui->tableWidget->selectColumn(logicalIndex);
}

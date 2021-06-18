#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDebug>

#include "device.hpp"

#define COLUMN_MANUFACTURER 0
#define COLUMN_MODEL 1

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , rowCount(0)
    , columnCount(2)
{
    ui->setupUi(this);

    {
        int row = 0;

        devList.addDevice(Device(row, "Intel", "Core i9-10980XE"));
        devList.addDevice(Device(++row, "AMD", "EPYC 7452"));
        devList.addDevice(Device(++row, "Intel", "Core i5-10400F"));
        devList.addDevice(Device(++row, "Intel", "Core i3-10100F"));
        devList.addDevice(Device(++row, "AMD", "Ryzen 5 PRO 4650G"));
    }

    rowCount = devList.count();

    ui->tableWidget->setColumnCount(columnCount);
    ui->tableWidget->setRowCount(rowCount);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList({"Manufacturer", "Model"}));

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

    ui->tableWidget->resizeColumnsToContents();

    connect(ui->tableWidget, &QTableWidget::itemChanged,
            this, &MainWindow::itemChanged);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sortIndicatorChanged,
            this, &MainWindow::sortHeader);
//    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked,
//            this, &MainWindow::columnSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButtonSortAscending_released()

{
    ui->tableWidget->sortByColumn(ui->tableWidget->currentColumn(),
                                  Qt::AscendingOrder);
}

void MainWindow::on_radioButtonSortDescending_released()
{
    ui->tableWidget->sortByColumn(ui->tableWidget->currentColumn(),
                                  Qt::DescendingOrder);
}

void MainWindow::on_pushButtonOutput_clicked()
{
    for (int row = 0; row < rowCount; ++row)
        qDebug() << QString::fromStdString(devList.findDevice(row)->manufacturer())
                 << QString::fromStdString(devList.findDevice(row)->model());
    ui->tableWidget->item(0, COLUMN_MANUFACTURER)->setSelected(true);
}

void MainWindow::itemChanged(QTableWidgetItem *item)
{
    switch (item->column()) {
    case COLUMN_MANUFACTURER:
        devList.findDevice(item->row())->setManufacturer(
                    item->data(Qt::DisplayRole).toString().toStdString());
        break;
    case COLUMN_MODEL:
        devList.findDevice(item->row())->setModel(
                    item->data(Qt::DisplayRole).toString().toStdString());
        break;
    default:
        return;
    }
}

void MainWindow::sortHeader(int logicalIndex, Qt::SortOrder order)
{
    switch (order) {
    case Qt::AscendingOrder:
        ui->radioButtonSortAscending->setChecked(true);
        break;
    case Qt::DescendingOrder:
        ui->radioButtonSortDescending->setChecked(true);
        break;
    }
    ui->tableWidget->selectColumn(logicalIndex);
}

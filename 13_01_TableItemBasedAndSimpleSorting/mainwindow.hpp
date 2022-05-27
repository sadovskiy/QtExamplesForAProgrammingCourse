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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "devicelist.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTableWidgetItem;
class Device;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Инициализация примера списка
    void init();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Методы по манипуляции модели пользовательского интерфейса
private slots:
    // Методы определения порядка сортировки
    void on_radioButtonSortDescending_released();
    void on_radioButtonSortAscending_released();

    // Метод контрольного вывода в консоль содержимого связного списка
    void on_pushButtonOutput_clicked();

    // Если данные в ячейках редактировались, то надо их перенести
    // в контейнер devList, иначе изменения останутся только в ячейке tableWidget
    // Этот метод будет переносить данные из ячейки в контейнер
    void itemChanged(QTableWidgetItem *item);
    // Если был изменён порядок сортировки в интерфейсе нажатием
    // на заголовок столбца, то надо переключить radioButtonSort* в соответствии
    // с положением флажка на столбце
    void sortHeader(int logicalIndex, Qt::SortOrder order);

private:
    // Далее данные модели пользовательского интерфейса
    Ui::MainWindow *ui;

    // Создаём связанный список
    DeviceList devList;

    // Количество строк и столбцов
    int rowCount;
    int columnCount;
};
#endif // MAINWINDOW_HPP

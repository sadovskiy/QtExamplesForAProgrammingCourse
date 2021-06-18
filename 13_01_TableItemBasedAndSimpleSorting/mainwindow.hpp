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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButtonSortDescending_released();
    void on_radioButtonSortAscending_released();

    void on_pushButtonOutput_clicked();

    void itemChanged(QTableWidgetItem *item);
    void sortHeader(int logicalIndex, Qt::SortOrder order);

private:
    Ui::MainWindow *ui;
    DeviceList devList;
    int rowCount;
    int columnCount;
};
#endif // MAINWINDOW_HPP

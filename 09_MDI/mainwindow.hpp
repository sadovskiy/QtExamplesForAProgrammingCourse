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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MdiChild;
class QMdiSubWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Методы позволяющие создавать, открывать и сохранять файл
    void newFile();
    void open();
    void save();
    void saveAs();

    // Методы позволяющие вырезать, скопировать и вставлять текст
    void cut();
    void copy();
    void paste();

    // Метод создающий новое дочернее окно на основе динамического
    // экземпляра класса MdiChild
    MdiChild *createMdiChild();

protected:
    // Для вопроса о сохранении файла при закрытии главного окна,
    // если в одном из дочерних окон файл был изменён
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    // Метод возвращающий указатель на активное дочернее окно
    MdiChild *activeMdiChild();
    // Метод поиска окна по имени файла
    QMdiSubWindow *findMdiChild(const QString &fileName);
};

#endif // MAINWINDOW_HPP

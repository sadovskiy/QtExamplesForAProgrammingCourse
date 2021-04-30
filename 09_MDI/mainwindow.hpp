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
class QSignalMapper;
class QString;
class QMdiSubWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();

    void cut();
    void copy();
    void paste();

    MdiChild *createMdiChild();
    void setActiveSubWindow(QWidget *window);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    MdiChild *activeMdiChild();
    QMdiSubWindow *findMdiChild(const QString &fileName);
};

#endif // MAINWINDOW_HPP

/*
 *
 * Copyright (C) 2016 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2016 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Методы и данные работают подобно примеру MDI
private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    bool maybeSave();

    void cut();
    void copy();
    void paste();

    void openFile(const QString& fileName);
    bool saveFile(const QString& fileName);
    void documentWasModified();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QString currentFileName; // Имя открытого файла
    bool isUntitled;         // Файл без названия

    void setCurrentFile(const QString& fileName);
    QString strippedName(const QString& fullFileName);
};

#endif // MAINWINDOW_H

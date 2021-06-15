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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Для работы с подсветкой текста надо создать указатель-член класса,
// а для этого надо сделать упреждающее объявление класса
class TextSyntaxHighlighter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonFind_clicked();
    void on_pushButtonApply_clicked();
    void on_lineEditValidate_textChanged(const QString &arg1);
    void on_pushButtonReplace_clicked();

private:
    Ui::MainWindow *ui;
    TextSyntaxHighlighter *highlighter; // Создаём указатель на объект подсветки
};
#endif // MAINWINDOW_HPP

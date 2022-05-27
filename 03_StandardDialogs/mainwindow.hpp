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

/*
 * Тут объявляем классы, чтобы не подключать библиотеки через "#include"
 * потому, что нам для объявления указателя весь класс не нужен.
 */
class QErrorMessage;
class QPrinter;
class QTextDocument;
class QProgressDialog;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Далее перечислены слоты кнопок, вызывающие соответствующие диалоговые окна
private slots:
    void on_pushButtonGetInt_clicked();
    void on_pushButtonGetDouble_clicked();
    void on_pushButtonGetItem_clicked();
    void on_pushButtonGetText_clicked();
    void on_pushButtonGetExistingDirectory_clicked();
    void on_pushButtonGetOpenFileName_clicked();
    void on_pushButtonGetOpenFileNames_clicked();
    void on_pushButtonGetSaveFileName_clicked();
    void on_pushButtonErrorShowMessage_clicked();
    void on_pushButtonAboutQt_clicked();
    void on_pushButtonAbout_clicked();
    void on_pushButtonMBoxInformation_clicked();
    void on_pushButtonMBoxQuestion_clicked();
    void on_pushButtonMBoxWarning_clicked();
    void on_pushButtonMBoxCritical_clicked();
    void on_pushButtonGetFont_clicked();
    void on_pushButtonGetColor_clicked();
    void on_pushButtonPrint_clicked();
    void on_pushButtonPageSetup_clicked();
    void on_pushButtonPrintPreview_clicked();
    void printPreviewNeeds(QPrinter *m_printer);
    void on_pushButtonProgress_clicked();

    void updateProgress();
    void cancel();

private:
    Ui::MainWindow *ui;

    /*
     * Диалоговое окно сообщений об ошибках создаётся, как член класса
     * для того, чтобы работал "checkBox" (флаг с текстовой меткой).
     */
    QErrorMessage *errorMessageDialog;

    // Контейнер для форматированного текста необходим для диалога печати.
    QTextDocument *textDoc;

    // Устройство принтер, куда будет осуществляться печать.
    QPrinter *printer;

    /*
     * Диалоговое окно индикатора прогресса, таймер и текущий шаг прогресса
     * для корректной работы должны быть в глобальной области видимости и
     * в динамической памяти.
     */
    QProgressDialog *progressDialog;
    QTimer *timer;
    int steps;
};

#endif // MAINWINDOW_HPP

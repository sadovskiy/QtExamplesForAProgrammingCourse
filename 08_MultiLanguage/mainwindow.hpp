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
#include <QTranslator>

namespace Ui {
class MainWindow;
}

/// Делаем предварительное(опережающее, упреждающее) объявление
class QActionGroup;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// Для демонстрации работы с диалоговым окном создадим слот "open()"
    void open();

    /// Слот (метод) переключает язык программы
    void switchLanguage(QAction *action);

private:
    Ui::MainWindow *ui;

    /**
     * Создадим два объекта управляющих переводом текстов в нашем приложении.
     * Первый для слов из нашего приложения "app"
     * Второй для слов из стандартных сообщений Qt (различные диалоговые окна)
     */
    QTranslator appTranslator;
    QTranslator qtTranslator;

    /// Список доступных переводов в меню будет формироваться динамически
    QActionGroup *languageActionGroup;
    QLabel *label;
    /// Переменная где будет храниться путь к файлам перевода "*.qm"
    QString qmPath;

    /// Метод для создания языкового меню
    void createLanguageMenu();
};

#endif // MAINWINDOW_HPP

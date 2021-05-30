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

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Соединение сигнала нажатия на кнопку и слота класса "MainWindow"
    connect(ui->pushButtonPrimary, &QPushButton::clicked,
            this, &MainWindow::setTextInLabel);
    /* где
     * "ui->pushButtonPrimary" - объект, который испускает сигнал.
     * "clicked()" - сигнал, испускаемый при нажатии на кнопку.
     * "this" - объект, где располагается слот.
     * "setTextInLabel()" - слот, который предназначен для обработки сигнала.
     */

    // Бываю ситуации, когда сигнал и/или слот могут быть перегружены
    // и тогда новый синтаксис связи сигнала со слотом может не работать,
    // выдавая ошибку «unresolved overloaded function type».
    // Причина кроется в том, что раньше при соединении сигнала со слотом
    // указывался тип аргумента как сигнала, так и слота,
    // а при использовании нового синтаксиса передаётся только
    // имя самого сигнала и/или слота.

    // Пример как выглядела раньше связь (следует обратить внимание на аргументы)
//    connect(ui->spinBox, SIGNAL(valueChanged(int)),
//            this,        SLOT(setValue(int)));

    // И в новом синтаксисе (если хотите увидеть ошибку раскомментируйте пример)
//    connect(ui->spinBox, &QSpinBox::valueChanged,
//            this,        &MainWindow::setValue);

    // В новом варианте всё работает хорошо пока сигнал и/или слот
    // не являются перегруженными, как в нашем примере.
    // Тут сигнал valueChanged() является перегруженным.
    // Есть вариант сигнала для int и QString.
    // Решение проблемы существует в двух вариантах
    // 1. Используя синтаксис C++ до 14 версии
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this,        &MainWindow::setValue);

    // 2. Используя синтаксис C++ после 14 версии
//    connect(ui->spinBox, qOverload<int>(&QSpinBox::valueChanged),
//            this,        &MainWindow::setValue);

    // Для переключения версии языка C++ откройте файл настройки проекта (.pro)
    // и там измените параметр CONFIG += c++11

    // Подробнее можно посмотреть по следующим ссылкам:
    // 1. https://doc.qt.io/qt-5/signalsandslots-syntaxes.html
    // 2. https://wiki.qt.io/New_Signal_Slot_Syntax
    // 3. https://wiki.qt.io/New_Signal_Slot_Syntax/ru
    // 4. https://stackoverflow.com/questions/16794695/connecting-overloaded-signals-and-slots-in-qt-5

    // Ещё один вариант связи перегруженных сигналов/слотов
    // с использованием ссылок показан в примере 11_Delegate.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSecondary_clicked(bool checked)
{
    /*
     * Если кнопка "pushButtonSecondary" нажата,
     * то включается связь сигнала перемещения "horizontalSlider"
     * со слотом установки значения "progressBarSecondary"
     */
    if (checked)
        connect(ui->horizontalSlider, &QSlider::valueChanged,
                ui->progressBarSecondary, &QProgressBar::setValue);
    // В противном случае разорвать связь
    else
        disconnect(ui->horizontalSlider, &QSlider::valueChanged,
                   ui->progressBarSecondary, &QProgressBar::setValue);
}

// Слот будет вызываться при нажатии на кнопку "pushButtonPrimary"
void MainWindow::setTextInLabel()
{
    // Записываем текст из поля ввода в метку.
    //    QString str = ui->lineEdit->text();
    //    ui->label->setText(str);

    // Или более короткий вариант того же самого
    // без использования временной переменной.
    ui->label->setText(ui->lineEdit->text());
}

// Слот для примера с перегрузкой сигнала QSpinBox::valueChanged()
void MainWindow::setValue(const int value)
{
    ui->progressBarSecondary->setValue(value);
}

void MainWindow::on_actionLineEditTextChenged_triggered(bool checked)
{
    // Аналогично описанию выше для кнопки,
    // но тут сигнал испускается при редактировании
    // текста в поле "lineEdit"
    if (checked)
        connect(ui->lineEdit, &QLineEdit::textChanged,
                ui->label, &QLabel::setText);
    else
        disconnect(ui->lineEdit, &QLineEdit::textChanged,
                   ui->label, &QLabel::setText);

}

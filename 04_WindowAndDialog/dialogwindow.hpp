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

#ifndef DIALOGWINDOW_HPP
#define DIALOGWINDOW_HPP

#include <QDialog>

namespace Ui {
class DialogWindow;
}

class DialogWindow : public QDialog
{
    Q_OBJECT

    // Одним из способов обмена данными с другими окнами является
    // использование переменных, куда можно скидывать на время информацию
    // из внутренних компонентов, таких как ui->lineEdit
    // Сделаем такую переменную
    QString mStr;

public:
    explicit DialogWindow(QWidget *parent = nullptr);
    ~DialogWindow();

    // Методы для передачи данных в окно созданного от этого класса
    void setString(const QString& str) {mStr = str;}
    // и метод для получения данных во вне из объекта этого класса
    QString string() const {return mStr;}
    // Вышем методы содержат не только объявления прототипа метода,
    // но и реализацию. Такие методы называются "инлайн"

    // Другой вариант обойтись без промежуточной переменной mStr
    // и обмениваться информацию напрямую с объектом ui->lineEdit
    // Метод для передачи данных в окно созданное от этого класса
    void setData(const QString& str);
    // и метод для получения данных во вне из объекта этого класса
    QString data() const;
    // Ещё можно сделать реализацию методов в файле dialogwindow.cpp


private slots:
    // Создадим метод (слот), который будет вызываться в случае редактирования
    // пользователя текста в компоненьте ui->lineEdit
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::DialogWindow *ui;
};

#endif // DIALOGWINDOW_HPP

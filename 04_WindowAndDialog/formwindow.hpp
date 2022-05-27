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

#ifndef FORMWINDOW_HPP
#define FORMWINDOW_HPP

#include <QWidget>

namespace Ui {
class FormWindow;
}

class FormWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FormWindow(QWidget *parent = nullptr);
    ~FormWindow();

    // Для одномоментного обмена данными удобно использовать структуру
    // Например объединить имя пользователя и пароль
    struct UserData {
        QString userName; // Имя пользователя
        QString password; // Пароль
    };

    // Методы для передачи данных в окно созданного от этого класса
    void setUserData(const UserData &ud);
    // и метод для получения данных во вне из объекта этого класса
    UserData userData() const;

    // Метод заполняющий поля ui->lineEditUserName и ui->lineEditPassword
    // из переменной currentData
    void currentDataToLineEditFild();

signals:
    void valueChanged(FormWindow::UserData &ud);

private slots:
    // Слоты отрабатывающие нажатие на кнопки OK и Cancel
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::FormWindow *ui;

    // Переменная хранящая набор данных такие, как имя пользователя и пароль
    UserData currentData;
};

#endif // FORMWINDOW_HPP

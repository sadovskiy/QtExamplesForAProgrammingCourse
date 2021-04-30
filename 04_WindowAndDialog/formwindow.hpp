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
    struct UserData {
        QString userName;
        QString password;
    };

    void setUserDataWin(const UserData &ud);
    UserData userDataWin() const;

    explicit FormWindow(QWidget *parent = nullptr);
    ~FormWindow();

signals:
    void valueChanged(FormWindow::UserData ud);

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::FormWindow *ui;
    UserData currentData;
};

#endif // FORMWINDOW_HPP

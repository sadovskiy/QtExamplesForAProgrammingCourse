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

    QString mStr;

public:
    explicit DialogWindow(QWidget *parent = nullptr);
    ~DialogWindow();

    void setString(const QString& str) {mStr = str;}
    QString string() const {return mStr;}

    // Или без промежуточной переменной mStr и реализация методов в файле cpp
    void setData(const QString& str);
    QString data() const;


private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::DialogWindow *ui;
};

#endif // DIALOGWINDOW_HPP

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

// Библиотека, содержащая описание класса главного окна
#include <QMainWindow>

// Пространство имён, содержащее упреждающее объявление "MainWindow",
// которое формируется по форме из файла "mainwindow.ui"
namespace Ui {
class MainWindow;
}

/*
 * Так как членами класса будут указатели на соответствующие объекты,
 * то вместо подключения библиотек можно просто сделать упреждающее объявление
 * соответствующих классов "QPushButton" и "QLabel"
 */
class QPushButton;
class QLabel;

class MainWindow : public QMainWindow
{
    /*
     * Макрос обязательный в приложениях Qt. Сообщает Qt,
     * что файл перед сборкой обычным компилятором (например GCC)
     * необходимо сначала обработать мета-объектным компилятором Qt.
     *
     * Если добавили после сборки проекта, то надо удалить старые файл проекта
     * и пересобрать заново, а то будет вылезать ошибка компиляции
     * "undefined reference to `vtable for TableModel'"
     */
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Слоты, это специальные методы, которые вызываются на возникающие сигналы
private slots:
    /*
     * Слот, вызываемый по сигналу "clicked()",
     * созданный из дизайнера форм QtCreator.
     * То есть не вручную написан.
     * В этом случае, имеет большое значение название слота
     * он обязан называться "void on_имяОбъекта_имяСигнала()"
     */
    void on_pushButton_clicked();

    /*
     * Слот, создаваемый нами (вручную) может называться как угодно,
     * но желательно в названии отразить его функции
     */
    void pushButtonClicked();

private:
    Ui::MainWindow *ui; // Указатель на объект формы из файла "mainwindow.ui"

    // Указатели на динамические объекты кнопка "pushButton" и метка "label"
    QPushButton *pushButton;
    QLabel      *label;
};

#endif // MAINWINDOW_HPP

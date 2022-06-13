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

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QListWidget>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Поскольку используется разделитель splitter, у которого можно выставлять
    // пропорции объектов в главном окне, то удобно этим воспользоваться
    // Первый аргумент порядковый номер объекта textEdit,
    // а второй его доля в занимаемой области
    ui->splitter->setStretchFactor(0, 1);
    // Первый аргумент порядковый номер объекта listWidget,
    // а второй его доля в занимаемой области
    ui->splitter->setStretchFactor(1, 2);

    // Для возможности редактировать текст свяжем сигнал itemClicked,
    // с слотом clickedItem. Сигнал в объекте ui->listWidget испускается когда
    // пользователь указателем мыши выбирает определённую строку в списке
    connect(ui->listWidget, &QListWidget::itemClicked,
            this, &MainWindow::clickedItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Метод срабатывает при выборе пользователем пункта "Open" в главном меню
void MainWindow::on_actionOpen_triggered()
{
    // Вызываем стандартное диалоговое окно открытия файла.
    // Откуда получаем путь и имя файла когда его выберет пользователь
    QString filePathAndName = QFileDialog::getOpenFileName(this);

    // Проверяем выбрал ли пользователь какой-нибудь файл
    if (!filePathAndName.isEmpty())
        // Если выбрал, то переходим к методу загрузки данных
        loadFile(filePathAndName);
}

// Метод срабатывает при выборе пользователем пункта "Save" в главном меню
void MainWindow::on_actionSave_triggered()
{
    // Вызываем стандартное диалоговое окно сохранения файла.
    // Откуда получаем путь и имя файла когда его выберит пользователь
    QString filePathAndName = QFileDialog::getSaveFileName(this);

    // Проверяем выбрал ли пользователь какой-нибудь файл
    if (!filePathAndName.isEmpty())
        // Если выбрал, то переходим к методу сохранения данных
        saveFile(filePathAndName);
}

// В этом слоте добавляем возможность редактировать строки
void MainWindow::clickedItem(QListWidgetItem *item)
{
    // Через указатель item получаем строку выбранную указателем мыши
    // и добавляем флаг редактирования Qt::ItemIsEditable к уже имеющимся
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    // Теперь строки можно редактировать
}

void MainWindow::loadFile(const QString &filePathAndName)
{
    // Заводим объект file, который получив путь к реальному файлу на ФС,
    // будет ассоциирован с ним
    QFile file(filePathAndName);
    // Пытаемся открыть файл как текстовой
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        // Если не получилось, то выводим пользователю сообщение об этом
        // и за счёт метода errorString(), говорим причину
        QMessageBox::warning(this,
                             tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(filePathAndName)
                             .arg(file.errorString()));
        // Дальше работать нет смысла, по этому выходим из функции
        return;
    }

    // Если попадаем сюда, то файл открылся и с ним можно работать дальше

    // Создаём поток на чтение
    QTextStream in(&file);

    // Переводим указатель мыши в вид часов ожидания
    QApplication::setOverrideCursor(Qt::WaitCursor);
    // Если пользователь выбрал вариант отображения файла объектом ui->textEdit
    if (ui->radioButtonTE->isChecked()) {
        // Загружаем сразу весь файл в объект textEdit.
        // Данный метод надо использовать с осторожностью, так как на больших
        // файлах может зависать
        ui->textEdit->setPlainText(in.readAll());
    }

    // Если пользователь выбрал вариант отображения файла объектом ui->listWidget
    if (ui->radioButtonLW->isChecked()) {
        // В этом случае мы работаем с объектом, который хранит данные в виде
        // списка, по этому загрузка сразу всего текста тут не подходит.
        // Тут лучше использовать загрузку данных по строкам,
        // а для этого необходимо использовать цикл, который прервётся,
        // когда чтение файла дойдёт до конца и метод atEnd() вернёт true.
        while (!in.atEnd()) {
            // Метод readLine() читает строку из потока in и возвращает
            // в метод addItem(), который добавляет её в конец списка
            ui->listWidget->addItem(in.readLine());
        }
    }

    // Возвращаем курсор мыши к прежниму виду
    QApplication::restoreOverrideCursor();

    // Выводим имя открытого файла в метку
    ui->label->setText(QFileInfo(filePathAndName).fileName());

    // Можно закрыть файл
    file.close();
}

void MainWindow::saveFile(const QString &filePathAndName)
{
    // Работает аналогично методу чтения файла
    QFile file(filePathAndName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(filePathAndName).arg(file.errorString()));
        return;
    }

    QTextStream out(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    if (ui->radioButtonTE->isChecked()) {
        // Получаем сразу всё содержимое объекта ui->textEdit и
        // через перегруженную операцию "поместить в поток" и выводим в
        // поток out
        out << ui->textEdit->toPlainText();
    }

    if (ui->radioButtonLW->isChecked()) {
        // Узнаём количество строк в списке ui->listWidget
        int count = ui->listWidget->count();
        // В случае работы со списком ui->listWidget,
        // запись строк происходит построчно
        for (int index = 0; index < count; ++index) {
            // Получаем строку по индексу index, добавляем перевод строки
            // и выводим её в поток out
            out << ui->listWidget->item(index)->text() + "\n";
        }
    }

    QApplication::restoreOverrideCursor();

    ui->label->setText(QFileInfo(filePathAndName).fileName());

    // Можно закрыть файл
    file.close();
}

/* *
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
#include "dialogwindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , autoGlobWindow(this)
  , dynamicWndowD(nullptr)
  , windowCountD(0)
  , windowCountP(0)
{
    // Следует помнить, все обращения к объектам на форме через указатель ui
    // должны быть после вызова этого метода
    ui->setupUi(this);
    // Для окна образованного от класса QWidget,
    // что бы оно было отдельным окном надо задовать свойство Qt::Window
    autoGlobWindow.setWindowFlag(Qt::Window);

    // Для получения данных из окна можно воспользоваться созданным
    // в нём сигналом valueChanged присоединив его
    // к методу setStatusBarMessage()
    connect(&autoGlobWindow, &FormWindow::valueChanged,
            this, &MainWindow::setStatusBarMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonDialogWindowA_clicked()
{
    // Создадим окно как локальную переменную
    // с автоматической продолжительностью хранения
    DialogWindow dialog(this);

    // Покажем и передадим окну управление
    // при этом произойдёт блокировка главного окна
    dialog.exec();

    // У окна созданного от класса QDialog (DialogWindow его наследник)
    // Есть встроенные методы accept() и reject(),
    // которые позволяют узнать, что нажал пользователь через метод result()
    // Привязка кнопок OK и Cancel к слотам accept() и reject() соответственно,
    // выполнена на форме в файле dialogwindow.ui,
    // через редактор сигналов/слотов

    // Посмотрим, что нажал пользователь, OK или Cancel
    if (dialog.result() == DialogWindow::Accepted)
        // Если он нажал OK, то через вызов метода string()
        // получим данные и выведем их в нижнюю панель окна
        ui->statusBar->showMessage(dialog.string());

    // Следует отметить, что после завершения функции окно dialog
    // будет удалено из памяти
}

void MainWindow::on_buttonFormWindowA_clicked()
{
    // Просто в качестве примера покажем как можно создать
    // и проинициализировать переменную типа UserData
    FormWindow::UserData ud = {"test", "test"};
    // и передать эти значения в окно autoGlobWindow
    autoGlobWindow.setUserData(ud);

    // Вызов метода currentDataToLineEditFild()
    // заполнит соответствующие поля данных в окне
    autoGlobWindow.currentDataToLineEditFild();

    // Так как окно было создано как член класса,
    // то оно уже существует и нам его надо просто показать
    autoGlobWindow.show();

    // Окно autoGlobWindow будет удалено из памяти,
    // только когда будет удалён объект this (mainWindow)
}

// Слот срабатывающий на сигнал FormWindow::valueChanged()
void MainWindow::setStatusBarMessage(const FormWindow::UserData &ud)
{
    // Воспользовавшись объектом ui->statusBar можно выводить информацию
    // в нижней части окна, а за счёт полученной переменной ud, можем вывести
    // содержимое полей ui->lineEditUserName и ui->lineEditPassword
    ui->statusBar->showMessage("User Name: " + ud.userName + \
                               " |Password: " + ud.password,
                               5000); // 5000 время отображения сообщения в мс
}

// Метод срабатывающий по нажатию на кнопку "New QWidget"
// панели "Dynamic Window via signal Destroyed" создаёт новое окно
// с динамической продолжительностью хранения
void MainWindow::on_buttonNewWindowD_clicked()
{
    // Создаём окно и передаём его адрес указателю dynamicWndowD
    dynamicWndowD = new FormWindow(this);
    // Увеличиваем счётчик окон для их учёта
    windowCountD++;
    // Говорим, что это окно и должно быть отдельным элементом
    dynamicWndowD->setWindowFlag(Qt::Window);
    // Проверяем, ставил ли пользователь отметку о модальности окна
    if (ui->checkBoxModalD->checkState() == Qt::Checked)
        // Если ставил, делаем окно модальным (блокирующим главное окно)
        dynamicWndowD->setWindowModality(Qt::WindowModal);

    // Тут следует отметить, что по умолчанию при закрытии окна,
    // в случае если оно глобально объявленное, статическое или динамическое,
    // оно не удаляется из памяти. В этих случаях нажатие на крестик в углу окна
    // или использование методо close() будет работать так же как и
    // вызов метода hide(), то есть будет просто скрывать окно.

    // Проверяем, ставил ли пользователь отметку об удалении окна из памяти
    // если оно было открыто. Это нужно, так как в противном случае окна будут
    // висеть в памяти даже после закрытия. При повторном вызове текущего метода
    // будет перезаписан указатель dynamicWndowD, а окно не будет удалено,
    // а просто скрыто. Из-за перезаписи указателя, возможность выйти
    // на это окно будет утеряна, что будет приводить к утечке памяти.
    if (ui->checkBoxDeleteOnCloseD->checkState() == Qt::Checked)
        // Одним из способов борьбы с этим является выставление атрибута
        // Qt::WA_DeleteOnClose, которое будет заставлять окна
        // удалятся из памяти после закрытия.
        dynamicWndowD->setAttribute(Qt::WA_DeleteOnClose);

    // Выводим окно на экран (до этого оно было скрыто)
    dynamicWndowD->show();

    // Следующая проблема возникает в связи с тем, что указатель
    // никак не проверить ссылается он на существующее окно или уже удалённое.
    // В случае обращения к удалённому окну программы рухнет.
    // Выходом было бы обнулять указатель окна после его удаления,
    // но в C++ не предусмотренно встроенных механизмов для этого.
    // Решить можно с помощью сигнала QObject::destroyed, который испускается
    // во время удаления окна. Его можно привязать к методу, который будет
    // обнулять указатель dynamicWndowD на окно и заодно уменьшать
    // счётчик windowCountD
    // В примере ниже это сделано через анонимную лямбда-функцию,
    // хотя можно сделать и обычным образом. Лямбда-функция используется
    // только для уменьшения размера кода.
    connect(dynamicWndowD, &QObject::destroyed,
            [&windowCountD=windowCountD, &dynamicWndowD=dynamicWndowD]() mutable
    {
        dynamicWndowD = nullptr;
        // Можно уменьшить счётчик созданных окон
        windowCountD--;
    });

    // Привязываем сигнал новых данные окна dynamicWndowD к слоту
    // отображающему их в нижней части окна MainWindow
    connect(dynamicWndowD, &FormWindow::valueChanged,
            this, &MainWindow::setStatusBarMessage);
    // Показываем пользователю количество созданных окон
    ui->spinBoxWindowCountD->setValue(windowCountD);
}

// Метод срабатывающий по нажатию на кнопку "Show Еxisting QWidget"
// панели "Dynamic Window via signal Destroyed" создаёт новое окно
// с динамической продолжительностью хранения
void MainWindow::on_buttonExistingWindowD_clicked()
{
    // В случае удаления объекта операцией delete эта проверка не поможет,
    // так как указатель не обнуляется, хотя объекта,
    // на который ссылается этот указатель уже нет.
    // Решение может заключаться в соединении сигнала destroyed() при
    // создании объекта с лямбда-функцией обнуления указателя
    // Что и реализовано в методе MainWindow::on_buttonNewWindowD_clicked()
    if (dynamicWndowD != nullptr)
        // Если окно есть (указатель не обнулён), то показываем окно
        dynamicWndowD->show();
}

// Метод срабатывающий по нажатию на кнопку "Delete Existing QWidget"
// панели "Dynamic Window via signal Destroyed" создаёт новое окно
// с динамической продолжительностью хранения
void MainWindow::on_buttonDeleteD_clicked()
{
    // Аналогично варианту выше
    if (dynamicWndowD != nullptr) {
        // Если окно есть (указатель не обнулён), то удаляем окно
        delete dynamicWndowD;
        // и обнуляем указатель
        dynamicWndowD = nullptr;
    }
}

// Метод срабатывающий по нажатию на кнопку "New QWidget"
// панели "Dynamic Window via QPointer" создаёт новое окно
// с динамической продолжительностью хранения
void MainWindow::on_buttonNewWindowP_clicked()
{
    // Другое решение по удалению объекта из памяти
    // Создаём окно и передаём его адрес указателю dynamicWndowP
    dynamicWndowP = new FormWindow(this);

    // Тут следует заметить, что мы используем специальный
    // указатель QPointer, который даёт возможность контролировать
    // своё состояние, в том числе удалять и обнулять содержимое,
    // что значительно упрощает работу.

    // Говорим, что это окно и должно быть отдельным элементом
    dynamicWndowP->setWindowFlag(Qt::Window);
    // Проверяем, ставил ли пользователь отметку о модальности окна
    if (ui->checkBoxModalP->checkState() == Qt::Checked)
        // Если ставил, делаем окно модальным (блокирующим главное окно)
        dynamicWndowP->setWindowModality(Qt::WindowModal);

    // Аналогично методу MainWindow::on_buttonNewWindowD_clicked() проверяем,
    // ставил ли пользователь отметку об удалении окна из памяти
    // если оно было открыто.
    // Следует заметить, что использование указателя QPointer
    // не избавляет нас от необходимости освобождать память и следить
    // за указателями. Этот указатель избавляет только от необходимости
    // использовать сигнал QObject::destroyed и обнулять указатель.
    // По этому это решение не лучше предыдущего, а просто другое
    if (ui->checkBoxDeleteOnCloseP->checkState() == Qt::Checked)
        dynamicWndowP->setAttribute(Qt::WA_DeleteOnClose);

    // Выводим окно на экран (до этого оно было скрыто)
    dynamicWndowP->show();

    // Привязываем сигнал новых данные окна dynamicWndowD к слоту
    // отображающему их в нижней части окна MainWindow
    connect(dynamicWndowP, &FormWindow::valueChanged,
            this, &MainWindow::setStatusBarMessage);
    // Увеличиваем счётчик окон для их учёта
    windowCountP++;
    // Показываем пользователю количество созданных окон
    ui->spinBoxWindowCountP->setValue(windowCountP);
}

// Метод срабатывающий по нажатию на кнопку "Show Еxisting QWidget"
// панели "Dynamic Window via QPointer" создаёт новое окно
// с динамической продолжительностью хранения
void MainWindow::on_buttonExistingWindowP_clicked()
{
    // Другое решение по удалению объекта
    // Тут вместо проверки на равенство nullptr,
    // проверяется есть что-то в указателе методом isNull()
    if (!dynamicWndowP.isNull())
        // Если окно есть , то показываем окно
        dynamicWndowP->show();
}

// Метод срабатывающий по нажатию на кнопку "Delete Existing QWidget"
// панели "Dynamic Window via QPointer" создаёт новое окно
// с динамической продолжительностью хранения
void MainWindow::on_buttonDeleteP_clicked()
{
    // Аналогично варианту выше
    if (!dynamicWndowP.isNull()) {
        // Можно уменьшить счётчик созданных окон
        --windowCountP;
        // Удаляем окно
        delete dynamicWndowP.data();
        // Следует заметить, что обнуление dynamicWndowP
        // происходит автоматический
    }
    // Показываем пользователю количество созданных окон
    ui->spinBoxWindowCountP->setValue(windowCountP);
}



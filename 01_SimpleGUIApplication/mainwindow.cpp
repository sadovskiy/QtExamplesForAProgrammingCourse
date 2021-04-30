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

/*
 * Файл, содержащий описание формы на языке C++
 * после прохождения файла "mainwindow.ui" мета-объектным компилятором Qt.
 */
#include "ui_mainwindow.h"

/*
 * Для возможности использовать кнопку и метку необходимо подключить
 * библиотеку "QPushButton" и "QLabel" соответственно.
 * Это необходимо только для динамических объектов, создаваемых программно.
 * Для объектов, созданных на форме  (файл "mainwindow.ui") этого не требуется,
 * так как в этом случае
 * это сделает MOC (англ. Meta-Object Compiler - мета-объектный компилятор).
 */
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , pushButton(nullptr) // Здесь обнуляем указатели, а память выделим под него ниже,
  , label(nullptr)       // хотя ничего не мешает нам это сделать и тут.
{
    /*
     * Метод создаёт компоненты формы по описанию из файла "mainwindow.ui".
     */
    ui->setupUi(this);

    /*
     * Создаём кнопку и метку в динамической памяти и
     * сразу делаем на них надпись.
     */
    pushButton = new QPushButton(tr("DynamicPushButton"));
    label = new QLabel(tr("DynamicLabel"));

    /*
     * Делаем привязку сигнала "clicked()" нажатия по кнопке к
     * слоту "pushButtonClicked()", который обрабатывает вывод
     * строки "Hello world!" в метку "label".
     */
    connect(pushButton, &QPushButton::clicked,
            this, &MainWindow::pushButtonClicked);

    // или старый вариант
    connect(pushButton, SIGNAL(clicked()),
            this, SLOT(pushButtonClicked()));


    /*
     * Задаём правила изменения размера для метки (по горизонтали и вертикали)
     * "Expanding" - занять максимум доступного пространства
     * "Preferred" - занимать стандартное пространство,
     * рекомендуемое для этого типа объекта.
     */
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    /*
     * Так как элементы динамические, необходимо их разместить на форме,
     * указав как их скомпоновать с уже имеющимися элементами.
     * Эти параметры работают, только если на форме (файл "mainwindow.ui")
     * включена компоновка в два столбца "formLayout"
     * Разместить кнопку и метку
     * "1" - во второй строке (отсчёт строк идёт от нуля)
     * "QFormLayout::LabelRole" - в первом столбце
     * "QFormLayout::FieldRole" - во втором столбце
     * Последним аргументом передаём, что собственно размещать.
     */
    //    ui->formLayout->setWidget(1, QFormLayout::LabelRole, label);
    //    ui->formLayout->setWidget(1, QFormLayout::FieldRole, pushButton);

    /*
     * Эти параметры работают, только если включена компоновка
     * по сетке "gridLayout".
     */
    ui->gridLayout->addWidget(label);
    ui->gridLayout->addWidget(pushButton);
    /*
     * В один момент времени должен быть включён только какой-то один
     * вариант компоновки главного окна и раскомментированы
     * соответствующие строки.
     * Например как сейчас включён "gridLayout" и расскоментированы строки
     * относящиеся к ниму.
     */
}

MainWindow::~MainWindow()
{
    delete label;
    delete pushButton;
    delete ui; // Удаляем созданный по форме (файл mainwindow.ui) компонент.
}

// Слот созданный в Qt Designer, через пункт меню "Перейти к слоту...".
void MainWindow::on_pushButton_clicked()
{
    /*
     * Выводим строку "Hello world!" в метку,
     * созданную на форме (файл "mainwindow.ui")
     * через дизайнер Qt Creator.
     */
    ui->label->setText(tr("Hello world!"));
}

// Слот созданый нами (вручную) прописыванием в секции "private slots".
void MainWindow::pushButtonClicked()
{
    // Выводим строку "Hello world!" в метку, созданную в динамической памяти.
    label->setText(tr("hello world!"));
}

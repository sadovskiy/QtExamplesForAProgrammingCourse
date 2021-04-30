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

#include <QInputDialog>
#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>

// Чтобы работало, надо добавить "printsupport" в файл "*.pro".
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>

#include <QProgressDialog>

#include <QStringList>
#include <QDir>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTimer>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  /*
       * Выделяем динамическую память для диалоговых окон,
       * контейнера, принтера, таймера и шага индикатора прогресса.
       */
  , errorMessageDialog(new QErrorMessage(this))
  , textDoc(new QTextDocument(this))
  , printer(new QPrinter)
  , progressDialog(new QProgressDialog(tr("Operation in progress."), // Заголовок.
                                       tr("Cancel"), // Текст на кнопке.
                                       0, // Минимальное значение индикатора.
                                       100, // Максимальное значение.
                                       this)) // Родителем для диалогового
  // окна будет главное окно.
  , timer(new QTimer(this))
  , steps(0) // Начальное значение шага индикатора прогресса.
{
    ui->setupUi(this);

    /*
     * Связываем сигнал закрытия окна со слотом, который остановит таймер и
     * обнулит шаг индикатора прогресса.
     */
    connect(progressDialog, &QProgressDialog::canceled,
            this, &MainWindow::cancel);

    // Делаем окно модальным.
    progressDialog->setModal(true);

    /*
     * Таймер, в определённый период времени испускает сигнал "timeout()",
     * который мы привязываем к слоту "updateProgress()", для движения
     * индикатора прогресса.
     * Периоды времени, через которые испускается сигнал, задаются
     * методом "start()" в миллисекундах, например "timer->start(1000)"
     * означает испускать сигнал "timeout()" раз в секунду.
     */
    connect(timer, &QTimer::timeout, this, &MainWindow::updateProgress);

    /*
     * Для того, чтобы окно "progressDialog" самопроизвольно не запускалось,
     * запускаем таймер с нулевым интервалом между сигналами "timeout()".
     */
    timer->start(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonGetInt_clicked()
{
    // Переменная, для контроля выбора пользователя кнопки "OK".
    bool ok;

    int iValue = QInputDialog::getInt(this, // Кто родитель диалогового окна.
                                      // Заголовок окна.
                                      tr("QInputDialog::getInteger()"),
                                      // Текст поясняющий, что требуется ввести.
                                      tr("Integer value:"),
                                      0, // Начальное значение.
                                      -10, // Минимальное значение.
                                      1000, // Максимальное значение.
                                      1, // Шаг изменения значения.
                                      &ok); // Пользователь нажал кнопку "OK".

    // Проверяем, нажал ли пользователь кнопку "OK".
    if (ok)
        // Вывод в сответствующую метку значения
        ui->labelGetInt->setText(QString::number(iValue));
    // или
    //    ui->labelGetInt->setText(QString("%1").arg(iValue));
    // или.
    //    ui->labelGetInt->setText(tr("%1").arg(iValue));
}

void MainWindow::on_pushButtonGetDouble_clicked()
{
    bool ok;

    double dValue = QInputDialog::getDouble(this,
                                            tr("QInputDialog::getDouble()"),
                                            tr("Double value:"),
                                            0.5,
                                            -10,
                                            1000,
                                            1.5,
                                            &ok);

    if (ok)
        ui->labelGetDouble->setText(QString::number(dValue));
}

void MainWindow::on_pushButtonGetItem_clicked()
{
    QStringList items; // Создаём строковый список.
    // Вносим в него названия времён года.
    items << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");

    bool ok;

    QString item = QInputDialog::getItem(this,
                                         tr("QInputDialog::getItem()"),
                                         tr("Season:"),
                                         // Пункты, которые будут в выпадающем списке.
                                         items,
                                         0, // Пункт открытый по умолчанию.
                                         // Можно ли редактировать пункты списка.
                                         false,
                                         &ok);

    // Проверяем, есть ли выбранный пункт пользователем.
    if (ok && !item.isEmpty())
        ui->labelGetItem->setText(item);
}

void MainWindow::on_pushButtonGetText_clicked()
{
    bool ok;

    QString text = QInputDialog::getText(this,
                                         tr("QInputDialog::getText()"),
                                         tr("Name:"),
                                         // Режим ввода (видимый или без отображения).
                                         QLineEdit::Normal,
                                         // Текст выводимый при открытии окна.
                                         tr("New user"),
                                         &ok);

    if (ok && !text.isEmpty())
        ui->labelGetText->setText(text);
}

void MainWindow::on_pushButtonGetExistingDirectory_clicked()
{
    QFileDialog::Options options; // Создаём переменную, отвечающую за настройки.

    // Записываем настройки диалогового окна.
    options = QFileDialog::DontUseNativeDialog | // Не использовать родной вид окна,
            // а использовать Qt-вид.
            QFileDialog::DontResolveSymlinks | // Не проходить по ссылкам.
            QFileDialog::ShowDirsOnly;         // Показывать только каталоги.

    QString directory =
            QFileDialog::getExistingDirectory(this,
                                              tr("QFileDialog::getExistingDirectory()"),
                                              // Использовать в качестве
                                              // начального каталога домашний.
                                              QDir::homePath(),
                                              // Применить настройки к окну.
                                              options);

    if (!directory.isEmpty())
        ui->labelGetExistingDirectory->setText(directory);
}

void MainWindow::on_pushButtonGetOpenFileName_clicked()
{
    QString fileName =
            QFileDialog::getOpenFileName(this,
                                         tr("QFileDialog::getOpenFileName()"),
                                         QDir::homePath(),
                                         /*
                                                                               * Фильтр для файлов
                                                                               * All Files (*), где слова "All Files"
                                                                               * увидит пользователь,
                                                                               * а "*" будет применино к каталогу
                                                                               * "*" - показывать все файлы
                                                                               * или
                                                                               * "*.txt" - показывать только текстовые файлы.
                                                                               * ";;" - резделитель фильтров.
                                                                               */
                                         tr("All Files (*);;Text Files (*.txt *.log)"));


    if (!fileName.isEmpty())
        ui->labelGetOpenFileName->setText(fileName);
}

void MainWindow::on_pushButtonGetOpenFileNames_clicked()
{
    QStringList files =
            QFileDialog::getOpenFileNames(this,
                                          tr("QFileDialog::getOpenFileNames()"),
                                          QDir::homePath(),
                                          tr("All Files (*);;Text Files (*.txt)"));

    // В случае со списком, надо проверять больше ли в списке позиций, чем ноль.
    if (files.count())
        ui->labelGetOpenFileNames->setText(QString("[%1]")
                                           // Использовать в качестве разделителя ", ".
                                           .arg(files.join(", ")));
}

void MainWindow::on_pushButtonGetSaveFileName_clicked()
{
    QString fileName =
            QFileDialog::getSaveFileName(this,
                                         tr("QFileDialog::getSaveFileName()"),
                                         QDir::homePath(),
                                         tr("All Files (*);;Text Files (*.txt)"));

    if (!fileName.isEmpty())
        ui->labelGetSaveFileName->setText(fileName);
}

void MainWindow::on_pushButtonErrorShowMessage_clicked()
{
    // В этом диалоговом окне есть флаг, при снятии которого окно больше
    // не будет отображаться.
    errorMessageDialog->showMessage(tr("This dialog shows error messages."));
}

void MainWindow::on_pushButtonAboutQt_clicked()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_pushButtonAbout_clicked()
{
    QMessageBox::about(this, tr("My Program"), tr("This is my program"));
}

void MainWindow::on_pushButtonMBoxInformation_clicked()
{
    /*
     * Переменная, которая будет хранить выбор пользователя,
     * то есть код нажатой им кнопки.
     */
    QMessageBox::StandardButton reply;

    reply = QMessageBox::information(this,
                                     tr("QMessageBox::information()"),
                                     // Текст сообщения.
                                     tr("This information message."));

    // Проверяем, что нажал пользователь.
    if (reply == QMessageBox::Ok)
        ui->labelMBoxInformation->setText(tr("OK"));
    else
        ui->labelMBoxInformation->setText(tr("Escape"));
}

void MainWindow::on_pushButtonMBoxQuestion_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this,
                                  tr("QMessageBox::question()"),
                                  tr("This question message?"),
                                  QMessageBox::Yes | // Определяем какие кнопки.
                                  QMessageBox::No  | // отображать на окне.
                                  QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
        ui->labelMBoxQuestion->setText(tr("Yes"));
    else if (reply == QMessageBox::No)
        ui->labelMBoxQuestion->setText(tr("No"));
    else
        ui->labelMBoxQuestion->setText(tr("Cancel"));
}

void MainWindow::on_pushButtonMBoxWarning_clicked()
{
    /*    QMessageBox::StandardButton reply;

    reply = QMessageBox::warning(this,
                                 tr("QMessageBox::warning()"),
                                 tr("This warning message!"),
                                 QMessageBox::Save |
                                 QMessageBox::Discard |
                                 QMessageBox::Cancel,
                                 QMessageBox::Save); // Вариант по умолчанию.

    if (reply == QMessageBox::Save)
        ui->labelMBoxWarning->setText(tr("Save"));
    else if (reply == QMessageBox::Discard)
        ui->labelMBoxWarning->setText(tr("Discard"));
    else
        ui->labelMBoxWarning->setText(tr("Cancel"));
*/

    // Ниже показан альтернативный вариант создания диалогового окна "QMessageBox".
    QMessageBox msgBox(QMessageBox::Warning,
                       tr("QMessageBox::warning()"),
                       tr("This warning message!"),
                       0, // Не будет кнопок при создании окна.
                       this);

    // Если нужно, что-то объяснить пользователю подробнее.
    msgBox.setDetailedText(tr("This is detailed text"));

    // Добавляем кнопки на окно, если требуются свои собственные.
    //    msgBox.addButton(tr("Save &Again"), QMessageBox::AcceptRole);
    //    msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);
    // или если использовать стандартные.
    msgBox.addButton(QMessageBox::Ok);
    msgBox.addButton(QMessageBox::Close);


    // Запускаем наше окно и после его закрытия пользователем проверяем,
    // что он нажал
    if (msgBox.exec() == QMessageBox::Ok)
        // или.
        //  if (msgBox.exec() == QMessageBox::AcceptRole)
        ui->labelMBoxWarning->setText(tr("Save Again"));
    else
        ui->labelMBoxWarning->setText(tr("Continue"));
}

void MainWindow::on_pushButtonMBoxCritical_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::critical(this,
                                  tr("QMessageBox::critical()"),
                                  tr("This critical message!"),
                                  QMessageBox::Abort |
                                  QMessageBox::Retry |
                                  QMessageBox::Ignore);

    if (reply == QMessageBox::Abort)
        ui->labelMBoxCritical->setText(tr("Abort"));
    else if (reply == QMessageBox::Retry)
        ui->labelMBoxCritical->setText(tr("Retry"));
    else
        ui->labelMBoxCritical->setText(tr("Ignore"));
}

void MainWindow::on_pushButtonGetFont_clicked()
{
    bool ok;

    QFont font = QFontDialog::getFont(&ok,
                                      QFont("Times", 12), // Начальный шрифт.
                                      this,
                                      "Select Font");
    if (ok) {
        // Отобразить шрифт, который выбрал пользователь и его параметры.
        ui->labelGetFont->setText(font.key());
        ui->labelGetFont->setFont(font); // Применить выбраный шрифт к метке.
    }
}

void MainWindow::on_pushButtonGetColor_clicked()
{
    const QColor color = QColorDialog::getColor(Qt::white,
                                                this,
                                                "Select Color");

    // Проверяем, выбрал ли пользователь цвет.
    if (color.isValid()) {
        // Выводит код цвета.
        ui->labelGetColor->setText(color.name());
        // Задаём цвет для метки.
        ui->labelGetColor->setPalette(QPalette(color));
        // Включаем заливку фона метки.
        ui->labelGetColor->setAutoFillBackground(true);
    }
}

void MainWindow::on_pushButtonPrint_clicked()
{
    // Создаём диалог вывода на принтер "printer".
    QPrintDialog printDialog(printer, this);

    // Создаём выводимый текст на печать.
    // В нашем случае для примера это будет Html.
    QString html = QString("<h1>%1</h1>").arg(ui->lineEditPrint->text());

    textDoc->setHtml(html); // Записываем Html код в контейнер "textDoc".

    // Если пользователь нажал кнопку "Печать".
    if (printDialog.exec() == QDialog::Accepted) {
        textDoc->print(printer); /// Печатаем
    }
}

void MainWindow::on_pushButtonPageSetup_clicked()
{
    // Вызываем окно настройки страницы у нашего принтера "printer".
    QPageSetupDialog setupDialog(printer, this);

    setupDialog.exec();
}

void MainWindow::on_pushButtonPrintPreview_clicked()
{
    QPrintPreviewDialog printPreviewDialog(printer, this);

    QString html = QString("<h1>%1</h1>").arg(ui->lineEditPrint->text());

    textDoc->setHtml(html);

    // Связываем сигнал запроса на рисование со слотом, который будет печатать.
    connect(&printPreviewDialog, &QPrintPreviewDialog::paintRequested,
            this, &MainWindow::printPreviewNeeds);

    printPreviewDialog.exec();
}

// Слот для печати.
void MainWindow::printPreviewNeeds(QPrinter *m_printer)
{
    textDoc->print(m_printer);
}

void MainWindow::on_pushButtonProgress_clicked()
{
    timer->start(50); // Запуск таймера и установка интервалов обновления в 50
    // миллисекунд.
}

void MainWindow::updateProgress()
{
    progressDialog->setValue(steps); // Задание положения индикатора прогресса.

    steps++;

    // Проверяем, что бы значение уровня индикатора не было больше 100.
    if (steps > progressDialog->maximum()) {
        timer->stop(); // Если больше 100 останавливаем таймер.
        steps = 0; // Обнуляем, чтобы при следующем отрытии "progressDialog"
        // начать сначала.
    }
}

void MainWindow::cancel()
{
    timer->stop(); // Остановить таймер, если пользователь нажал кнопку "Cancel".
    steps = 0;
}


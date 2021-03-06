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
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>
#include <QMdiSubWindow>
#include "mdichild.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Соединяем пункты меню со слотами
    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::open);
    connect(ui->actionNew, &QAction::triggered,
            this, &MainWindow::newFile);
    connect(ui->actionSave, &QAction::triggered,
            this, &MainWindow::save);
    connect(ui->actionSaveAs, &QAction::triggered,
            this, &MainWindow::saveAs);

    connect(ui->actionCut, &QAction::triggered,
            this, &MainWindow::cut);
    connect(ui->actionCopy, &QAction::triggered,
            this, &MainWindow::copy);
    connect(ui->actionPaste, &QAction::triggered,
            this, &MainWindow::paste);

    connect(ui->actionExit, &QAction::triggered,
            qApp, &QApplication::closeAllWindows);

    // Задаём заголовок окна. Его так же можно через свойства формы
    // в файле mainwindow.ui задать
    setWindowTitle(tr("Application MDI"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Открываем новый пустой документ
// со стандартным названием untitled%1.txt
void MainWindow::newFile()
{
    // Создаём новое окно
    MdiChild *child = createMdiChild();
    // Задаём ему базовые параметры
    child->newFile();
    // Выводим его в объекте ui->mdiArea
    child->show();
}

// Открываем файл
void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        // Выесняем, есть ли у нас уже документ с таким названием
        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) {
            // Если есть, то делаем его активным и выходим из метода
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        // Если такого файла ещё нет, то создаём новое окно
        MdiChild *child = createMdiChild();
        // и загружаем файл
        if (child->loadFile(fileName)) {
            // О чём сообщаем пользователю через нижнюю часть окна
            ui->statusBar->showMessage(tr("File loaded"), 2000);
            // Показываем окно
            child->show();
        } else {
            // Если загрузить не удалось, то удаляем только что
            // созданный экземпляр окна
            child->close();
        }
    }
}

// Сохраняем файл
void MainWindow::save()
{
    // Окон на области ui->mdiArea может быть много
    // определяем активное, так как скорее всего пользователь
    // про него говорил, когда выбирал пункт "Save".
    // У этого активного окна запускаем метод, который
    // сохранит файл
    if (activeMdiChild() && activeMdiChild()->save())
        statusBar()->showMessage(tr("File saved"), 2000);
}

// Сохранить файл с другим названием
void MainWindow::saveAs()
{
    // Аналогично предыдущему варианту
    if (activeMdiChild() && activeMdiChild()->saveAs())
        statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::cut()
{
    // Определяем текущее активное окно,
    // для использования метода cut().
    if (activeMdiChild())
        // Сам метод cut() прописан в базовом классе QTextEdit
        activeMdiChild()->cut();
}

void MainWindow::copy()
{
    if (activeMdiChild())
        activeMdiChild()->copy();
}

void MainWindow::paste()
{
    if (activeMdiChild())
        activeMdiChild()->paste();
}

// Метод по созданию дочернего окна в области ui->mdiArea
MdiChild *MainWindow::createMdiChild()
{
    // Создаём окно редактора
    MdiChild *child = new MdiChild;
    // Добавляем его в объект ui->mdiArea
    ui->mdiArea->addSubWindow(child);

    // По умолчанию пункты меню "Cut" и "Copy" отключены.
    // Связываем сигналы выделенного текста, для включения
    // этих пунктов в меню и выключения, если выделенного текста нет
    connect(child, &MdiChild::copyAvailable,
            ui->actionCut, &QAction::setEnabled);
    connect(child, &MdiChild::copyAvailable,
            ui->actionCopy, &QAction::setEnabled);

    return child;
}

// Так как в этом примере на одном главном окне располагается много
// отдельных окон в области ui->mdiArea, то перед закрытием главного
// окна их все надо позакрывать
void MainWindow::closeEvent(QCloseEvent *event)
{
    // Пытаемся закрыть все дочерние окна
    ui->mdiArea->closeAllSubWindows();
    // Проверяем закрылись ли все дочерние окна.
    if (ui->mdiArea->currentSubWindow())
        // Если есть какое-то активное окно,
        // то ждём пока его закроет пользователь
        event->ignore();
    else
        // Если все окна закрылись, то выходим
        event->accept();
}

// Метод вытаскивает активное дочернее окно
MdiChild *MainWindow::activeMdiChild()
{
    // Проблема в том, что метод ui->mdiArea->activeSubWindow() возвращает
    // указатель типа QMdiSubWindow, а нам нужен MdiChild.
    // По этому вытаскиваем указатьель типа QMdiSubWindow активного окна
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        // и делаем приведение типа к указателю MdiChild.
        // Тут переход к указателю типа QWidget нужен по тому,
        // что тип QMdiSubWindow, это другая ветвь по иерархии наследования.
        // По этому нам надо поднятся вверх по иерархии к более общему классу
        return qobject_cast<MdiChild *>(activeSubWindow->widget());

    // На случай если активного окна не было
    return nullptr;
}

// Метод поиска окна по имени файла
QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName)
{
    // Вначале определим полный путь к файлу и его имя,
    // что бы не было ошибки и путаницы. Вдруг есть ещё один файл с таким же
    // именем но в другом каталоге
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    // Теперь переберём все дочерние окна в поисках окна с
    for (auto *window : ui->mdiArea->subWindowList()) {
        // Полученный в текущей итерации цикла указатель приводим
        // к типу MdiChild
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        // Методом сравнения определяем, является ли имя файла
        // в текущем окне искомым именем.
        if (mdiChild->currentFile() == canonicalFilePath)
            // Если совпадают, значит окно найдено и мы
            // возвращаем указатель на него
            return window;
    }

    // На случай если окно не нашлось
    return nullptr;
}

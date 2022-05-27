/*
 *
 * Copyright (C) 2016 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2016 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
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
#include <QLibraryInfo>
#include <QCloseEvent>


// Тут комментарии практический отсутствуют, так как большинство решений
// уже было рассмотрено в примерах ранее и этот пример практический полностью
// повторяет пример с MDI

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , isUntitled(true)
{
    ui->setupUi(this);
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

    connect(ui->textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

    int static filenum = 0;

    currentFileName = QString("untitled%1.txt").arg(filenum++);

    setWindowTitle(currentFileName + "[*]"  + tr(" - Application SDI"));

    setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    // Единственная разница это создание нового окна
    // с динамической продолжительностью хранения
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString str = QFileDialog::getOpenFileName(this);
        if (!str.isEmpty()) {
            openFile(str);
        }
        setCurrentFile(str);
    }
}

bool MainWindow::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(currentFileName);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save As"),
                                                    currentFileName);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool MainWindow::maybeSave()
{
    if (ui->textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this,
                                   tr("Application SDI"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save |
                                   QMessageBox::Discard |
                                   QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::cut()
{
    ui->textEdit->cut();
}

void MainWindow::copy()
{
    ui->textEdit->copy();
}

void MainWindow::paste()
{
    ui->textEdit->paste();
}

void MainWindow::openFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             tr("Application SDI"),
                             tr("Cannot read file %1:\n%2")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
    ui->textEdit->setPlainText(in.readAll());
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             tr("Application SDI"),
                             tr("Cannot write file %1:\n%2")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();

    setCurrentFile(fileName);

    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFileName = fileName;
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);
    isUntitled = false;

    QString showName;

    if (currentFileName.isEmpty()) {
        showName = "untitled.txt";
        currentFileName = showName;
    }
    else
        showName = strippedName(currentFileName);

    setWindowTitle(tr("%1[*] - %2")
                   .arg(showName)
                   .arg(tr("Application SDI")));
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::documentWasModified()
{
    setWindowModified(ui->textEdit->document()->isModified());
}

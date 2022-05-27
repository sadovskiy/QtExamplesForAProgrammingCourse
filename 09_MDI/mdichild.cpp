/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "mdichild.h"

MdiChild::MdiChild(QWidget *parent):
    QTextEdit(parent)
  , isUntitled(true)
{
    // Удаляем окно из памяти, что бы не было утечек памяти
    setAttribute(Qt::WA_DeleteOnClose);
}

// Метод создаёт новый пустой файл
void MdiChild::newFile()
{
    // Для нумерации создаваемых файлов, пока им не присвоено имя
    static int sequenceNumber = 1;

    // Ставим метку, что файл без названия
    isUntitled = true;
    // Создаём имя документа по умолчанию, с использованием счётчика
    curFile = tr("untitled%1.txt").arg(sequenceNumber++);
    // Включаем добавление символа "*" в заголовок дочернего окна,
    // в качестве признака редактирования файла
    setWindowTitle(curFile + "[*]") ;

    // Связываем сигнал contentsChanged с слотом documentWasModified
    // для проставления признака редактирования текста в приложении
    connect(document(), &QTextDocument::contentsChanged,
            this, &MdiChild::documentWasModified);
}

// Стандартная загрузка файла
bool MdiChild::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    // Загружаем данные в текущее дочернее окно
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

    // Поскольку была загрузка, а значит текст изменился и значит надо
    // выставить признак редактирования
    connect(document(), &QTextDocument::contentsChanged,
            this, &MdiChild::documentWasModified);

    return true;
}

// При сохранении файла надо выяснить есть ли у него название
bool MdiChild::save()
{
    // Проверяем признак именования файла
    if (isUntitled) {
        // Если у файла нет имени
        return saveAs();
    } else {
        // Если есть, то используем текущие и сохраняем под ним
        return saveFile(curFile);
    }
}

// Сохранение файла через открытие диалогового окна сохранения файла,
// если у него не было имени и пути
bool MdiChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    // Путь и имя получили, теперь делаем сохранение файла
    return saveFile(fileName);
}

// Метод записывает файл из текстового потока
bool MdiChild::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             tr("MDI"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    // Скидываем из окна текст в поток файла
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    // Передаём новое имя файла в качестве основного
    setCurrentFile(fileName);
    return true;
}

// Оставим у файла только его имя. Убираем путь
QString MdiChild::userFriendlyCurrentFile()
{
    return QFileInfo(curFile).fileName();
}

// Если дочернее окно закрывается, то надо проверить
// был ли в нём отредактирован документ, и если да,
// то предложим пользователю его сохранить
void MdiChild::closeEvent(QCloseEvent *event)
{
    // Если пользователь нажмёт "Cancel",
    // то дочернее окно не закроется
    if (maybeSave())
        // Окно закрывается
        event->accept();
    else
        // Окно продолжит работать
        event->ignore();
}

// В классе QTextEdit, за работу с форматированными данными используется
// класс QTextDocument, у которого есть механизм определять,
// было ли редактирование текста или нет. Данный метод узнаёт это и
// передаёт эти сведенья текущему дочернему окну
void MdiChild::documentWasModified()
{
    setWindowModified(document()->isModified());
}

// Проверка, надо ли сохранять файл
bool MdiChild::maybeSave()
{
    // Если документ был изменён
    if (document()->isModified()) {
        // То предложим пользователю его сохранить
        // или выйти без сохранения
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this,
                                   tr("MDI"),
                                   tr("'%1' has been modified.\n"
                                      "Do you want to save your changes?")
                                   .arg(userFriendlyCurrentFile()),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

// Метод делает новый отредактированный файл текущим
// и даёт ему имя
void MdiChild::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    // Теперь у файла есть название
    isUntitled = false;
    // Теперь документ сохранён под новым именем и не является
    // изменённым
    document()->setModified(false);
    setWindowModified(false);
    // Используя новое имя файла надо обновить признак редактирования
    // в заголовке дочернего окна
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

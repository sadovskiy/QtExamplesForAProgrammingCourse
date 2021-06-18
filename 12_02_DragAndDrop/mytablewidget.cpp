/*
 *
 * Copyright (C) 2021 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2021 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

// В данном примере реализован вариант обработки переноса данных
// по технологии Drag and Drop. В качестве контейнера используется Item-Based
// компонент образованный от класса QTableWidget.
// Подробнее можно посмотреть в документации Qt
// https://doc.qt.io/qt-5/model-view-programming.html#using-drag-and-drop-with-item-views
// В частности, там приводится пример для работы с Model-Based компонентом.
// В данном примере активно применяется типы (форматы) MIME.
// Это стандартизированные форматы данных позволяющие обрабатывать данные
// в соответствии с правилами обработки для этого конкретного типа.
// Подробнее про них можно прочитать тут: https://ru.wikipedia.org/wiki/MIME

#include "mytablewidget.hpp"

#include <QDebug>
#include <QMimeData>
#include <QDrag>
#include <QList>
#include <QStringList>
#include <QApplication>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QStringList>
#include <QStandardItemModel>

bool MyTableWidget::hasFormat(const QString &format) const
{
    return currentMimeType == format;
}

MyTableWidget::MyTableWidget(QWidget *parent):
    QTableWidget(parent)
  // По умолчанию определяем тип как внутренний тип ячейки таблицы Qt.
  // Это внутренний бинарный MIME тип используемый только в библиотеке Qt
  // для ячеек таблицы
  , currentMimeType("application/x-qabstractitemmodeldatalist")
  , cr('\r')
  , lf('\n')
  , tab('\t')
  , comma(',')
  , semicolon(';')
  , quotes('\"')
  , columnDelimiter{',', ';', '\t'}
  , rowDelimiter{0x0d0a, 0x000a, 0x000d} // 0d0a (crlf)
  , currentColumnDelimiter(columnDelimiter[0])
  , currentRowDelimiter{0, '\n'}
  //  , currentRowDelimiter(QString("%1%2").arg(cr).arg(lf))
  //  , currentRowDelimiter({cr, lf})
  , thereAreQuotes(true)
{
    //    currentRowDelimiter = {cr, lf};
    qDebug() << currentColumnDelimiter << " " << currentRowDelimiter;
}

// Этот метод запускается, если пользователь пытается
// перетащить ячейку (ячейки) таблицы мышью.
// Аргументы itmes содержит список QList перетаскиваемых ячеек.
// В случае работы с моделью, есть аналогичный метод класса QAbstractItemModel
// описанный в документации Qt.
QMimeData *MyTableWidget::mimeData(const QList<QTableWidgetItem *> items) const
{
    // В таблице каждая ячейка это отдельный объект QTableWidgetItem.
    // Этот объект создаётся, когда происходит вставка данных,
    // иначе говоря, это означает, что клетка в таблице будет отрисована,
    // но если данные не были вставлены в ячейку,
    // то указатель этой клетки будет указывать на nullptr.
    // Поэтому перед работой с ячейкой необходимо удостовериться в том,
    // что она действительно есть.
    // Проверяем есть ли в списке указатели и если список пустой, то выходим.
    if (items.isEmpty())
        return nullptr;

    // Проверяем первую запись списка на наличие данных по указателю и,
    // если их нет, значит ячейка в таблице отсутствует,
    // а значит дальнейшая работа невозможна и пользователь не сможет
    // выбрать ячейку в таблице.
    // В качестве другого решения, можно было бы отправлять пустой mimeData.
    // Тогда можно было бы копировать несуществующую ячейку.
    if (items.at(0) == nullptr)
        return nullptr;
    // Пример другого решения
    // QMimeData *mimeData = new QMimeData;
    // mimeData->setText("");
    // return mimeData;


    // Сделаем возможность выбора типа MIME данных при реализации
    // операции "Взять и перетащить".
    QStringList types = mimeTypes();
    if (types.isEmpty())
        return nullptr;


    // Есть возможно работы с диапазонами ячеек в таблице,
    // которые выделил пользователь.
    // Для этого можно воспользоваться функцией selectedRanges().
    // Выделение осуществляется левой клавишей мыши
    // и одновременным зажатием клавиши «Shift» или клавиши «Ctrl».
    // Однако, следует знать одну особенность выделения ячеек через
    // удерживания этих клавиш.
    // Клавиша «Shift» выделяет один непрерывный диапазоны ячеек
    // и методы rowCount() или columnCount() будут возвращать
    // соответствующие количество ячеек,
    // а метод selectedRanges().count() вернёт всего один диапазон.
    // Клавиша «Ctrl» создаёт независимые блоки ячеек по одному элементу
    // и методы rowCount() или columnCount() будут возвращать число ячеек
    // в количестве одной, но диапазонов будет много
    // и метод selectedRanges().count() вернёт диапазонов столько,
    // сколь ячеек было выделено.
    // Ниже представлен пример работы с диапазонами выбранных ячеек
    //    for (int i = 0; i < selectedRanges().count(); ++i) {
    //        rowCount = selectedRanges().at(i).rowCount();
    //        columnCount = selectedRanges().at(i).columnCount();
    //    }

    // Так как под разные типы данных MIME используются разные способы подготовки к передаче данных
    if (hasFormat("text/plain") || hasFormat("text/csv") ) {
        QString result;

        /*
         * 1. item отсутствует
         * 2. Один item
         * 3. Группа item расположенных по горизонтали
         * 4. Группа item расположенных по вертикали
         * 5. Группа item расположенных прямоугольным блоком
         *
        */
        //        int top = INT_MAX;
        //        int left = INT_MAX;
        //        // Определяем верхний левый элемент
        //        top = qMin(r, top);
        //        left = qMin(c, left);

        int topSelectionRange = items.at(0)->row();
        int leftSelectionRange = items.at(0)->column();
        int rowCountSelectionRange = 0;
        int columnCountSelectionRange = 0;
        for (int i = 0; i < items.count(); ++i) {
            // Проверяем первый случай
            if (items.at(i) == nullptr)
                return nullptr;

            int c = items.at(i)->column() - leftSelectionRange;
            int r = items.at(i)->row() - topSelectionRange;

            if (c > 0 &&
                    (c < columnCountSelectionRange ||
                     items.at(i)->row() == topSelectionRange))
                result += currentColumnDelimiter;
            if (r > 0 && items.at(i)->column() == leftSelectionRange)
                result += currentRowDelimiter[1];
            if (thereAreQuotes)
                result += quotes +
                          items.at(i)->data(Qt::DisplayRole).toString() +
                          quotes;
            else
                result += items.at(i)->data(Qt::DisplayRole).toString();

            if (items.at(i)->row() == topSelectionRange)
                columnCountSelectionRange++;
            if (items.at(i)->column() == leftSelectionRange)
                rowCountSelectionRange++;
        }

        result += currentRowDelimiter[1];
        qDebug() << result;
        // Создаём объект формата MIME в который далее сложим обработанные данные.
        // Именно этот объект передаётся другим объектам
        // при перетаскивании указателем мыши.
        QMimeData *mimeData = new QMimeData;

        mimeData->setData(currentMimeType, result.toUtf8());
        return mimeData;
    }

    if (hasFormat("application/x-qabstractitemmodeldatalist")) {
        //        QDataStream stream(&codedData, QIODevice::WriteOnly);
        //        QMap<int,  QVariant> roleDataMap;

        //        for (int i = 0; i < items.count(); ++i) {
        //            roleDataMap[Qt::DisplayRole] = items.at(i)->data(Qt::DisplayRole);
        //            stream << items.at(i)->row() << items.at(i)->column() << roleDataMap;
        //        }

        return QTableWidget::mimeData(items);
    }
    return nullptr;
}

// Данный метод задаёт поддерживаемые типы MIME
QStringList MyTableWidget::mimeTypes() const
{
    QStringList types;
    // Собственно, тут задаём типы MIME,
    // с которыми наша программа сможет работать.
    types << "application/x-qabstractitemmodeldatalist"
          << "text/plain"
          << "text/csv";

    return types;
}

bool MyTableWidget::dropMimeData(int row, int column,
                                 const QMimeData *data,
                                 Qt::DropAction action)
{
    Q_UNUSED(action);
    if (data == nullptr)
        return false;

    if (data->hasFormat("application/x-qabstractitemmodeldatalist")) {
        return QTableWidget::dropMimeData(row, column, data, action);
    }

    if (data->hasFormat("text/plain")) {
        QStringList strings = data->text().split(lf);

        for (int rowSelected = 0; rowSelected < strings.count(); ++rowSelected) {
            if ((row + rowSelected) >= rowCount())
                insertRow(rowCount());
            QStringList tokens = strings[rowSelected].split(semicolon);
            for (int columnSelected = 0; columnSelected < tokens.count(); ++columnSelected) {
                QString token = tokens[columnSelected];
                token.remove(thereAreQuotes);
                if (token.isEmpty())
                    continue;
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(token);
                setItem(row + rowSelected, column + columnSelected, item);
            }
        }

        return true;
    }

    return false;
}

void MyTableWidget::setMimeType(const QString &newMimeType)
{
    if (newMimeType == "text/plain" ||
            newMimeType == "text/csv")
        emit enableDelimiterChange(true);
    else
        emit enableDelimiterChange(false);

    currentMimeType = newMimeType;
}

void MyTableWidget::setRowDelimiter(int newDelimiter)
{
//    currentRowDelimiter[0] = rowDelimiter[newDelimiter];
//    currentRowDelimiter[0] = 0x00;
    qDebug() << currentRowDelimiter;
}

void MyTableWidget::setColumnDelimiter(int newDelimiter)
{
    currentColumnDelimiter = columnDelimiter[newDelimiter];
    qDebug() << currentColumnDelimiter;
}

void MyTableWidget::setQuotes(bool state)
{
    thereAreQuotes = state;
}

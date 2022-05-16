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

// Подробно реализация механизма Модель-Представление-Контроллер описана в документации,
// например тут: https://doc.qt.io/qt-5/modelview.html
// и тут: https://ru.wikipedia.org/wiki/Model-View-Controller

#ifndef TABLEMODEL_HPP
#define TABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include <QTime>

class TableModel : public QAbstractTableModel
{
    // Если добавили после сборки проекта, то надо удалить старые файл проекта
    // и пересобрать заново, а то будет вылезать ошибка компиляции
    // "undefined reference to `vtable for TableModel'"
    Q_OBJECT

    // Список элементов, с которыми будем работать.
    // Это два связанные списка. Каждый список в нашем примере будет отдельным
    // столбцом. В общем случае так делать не рекомендуется.
    // Данные надо компоновать вместе, а не отдельными списками,
    // например объединив их через структуру или класс
    QList<QString> listStrA;
    QList<QString> listStrB;
    // Последний (третий) столбец в нашем примере будет отображать текущее время
    QTime time;
    // Число столбцов в нашей таблице
    const int columnsNum;

public:
    explicit TableModel(QObject *parent = nullptr);

    // Методы, возвращают количество элементов списка (строк) и столбцов
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // Метод, возвращает значение элементов из списков в ячейку таблицы
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    // Метод, возвращает новое значение элемента из ячейки в список
    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 int role = Qt::EditRole) override;
    // Метод, возвращает значение в заголовок таблицы
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Метод, возвращает параметры редактируемого элемента
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Метод, вставляет новую строку в модель
    void insertValue(const QString &value);
};

#endif // TABLEMODEL_HPP

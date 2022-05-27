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

// Подробно работа с делегатами описана в документации,
// например тут: https://doc.qt.io/qt-5/modelview.html
// раздел 3.4 Delegates.

#ifndef SPDELEGATE_HPP
#define SPDELEGATE_HPP

#include <QStyledItemDelegate>

// Аналогично, как и для работы с бинарными данными через
// класс CheckBoxDelegate, для работы с числами удобнее
// использовать QSpinBox
class SpinBoxDelegate : public QStyledItemDelegate
{
public:
    explicit SpinBoxDelegate(QWidget *parent = nullptr);

    // Метод, создающий виджет-редактор с QSpinBox
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    // Метод, передающий значение из таблицы в виджет-редактор
    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const;

    // Метод, передающий значение из виджета-редактора в таблицу
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const;

    // Метод, определяющий расположение виджета-редактора в таблице
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

    // Метод, описывающий как должна быть нарисована ячейка таблицы
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
};

#endif // SPDELEGATE_HPP

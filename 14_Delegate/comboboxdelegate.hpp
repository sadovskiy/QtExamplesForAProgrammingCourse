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

// Подробно работа с делегатами (Контроллерами) описана в документации,
// например тут: https://doc.qt.io/qt-5/modelview.html
// раздел 3.4 Delegates.

#ifndef COMBOBOXDELEGATE_HPP
#define COMBOBOXDELEGATE_HPP

#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    // Переменная будет хранить список значений для выбора в comboBox
    QStringList listOptions;

public:
    explicit ComboBoxDelegate(QWidget *parent = nullptr);

    // Метод, создающий виджет-редактор с отбъектом типа QComboBox
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    // Метод, передающий значение из таблицы в виджет-редактор
    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;
    // Метод, передающий значение из виджета-редактора в таблицу
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    // Метод, определяющий расположение виджета-редактора в таблице
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    // Метод, описывающий поведение ячейки как реакции на возникающие события
    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);

    // Метод, передающий диапазон значений в переменную listOptions.
    // Позволяет задать варианты в comboBox для выбора пользователем
    // в таблице
    void setData(const QStringList &strList);
};

#endif // COMBOBOXDELEGATE_HPP

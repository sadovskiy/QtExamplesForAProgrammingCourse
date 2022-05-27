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

#include "comboboxdelegate.hpp"

#include <QComboBox>
#include <QMouseEvent>
#include <QAbstractItemView>
#include <QDebug>
#include <QTableWidget>

ComboBoxDelegate::ComboBoxDelegate(QWidget *parent):
    QStyledItemDelegate(parent)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *comboBox = new QComboBox(parent);

    // Добавляем варианты из listOptions в comboBox
    comboBox->addItems(listOptions);
    // Задаём значение по умолчанию
    comboBox->setCurrentIndex(0);

    return comboBox;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);

    // Берём отображаемое значение index и выбираем его в качестве начального,
    // когда пользователь захочет раскрыть список
    comboBox->setCurrentText(index.data().toString());
}

void ComboBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    // Определяем текущий выбор пользователя для вставки в таблицу
    model->setData(index, comboBox->currentText());
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

bool ComboBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
    Q_UNUSED(option);
    // Определяем событие, такое как отпускание указателя мыши в ячейке
    if (event->type() == QEvent::MouseButtonRelease)
    {
        // Сделаем проверку для реакции только на нажатие по левой кнопки мыши
        if (static_cast<QMouseEvent *>(event)->button() == Qt::LeftButton) {
            // Привидение типа к QWidget для перехода к ui->tableWidget
            QWidget *widget = const_cast<QWidget *>(option.widget);
            // Для доступа к itemView как к QAbstractItemView
            QAbstractItemView* itemView = qobject_cast<QAbstractItemView *>(widget);

            // Проверяем удалось ли получить указатель
            // на объект типа QAbstractItemView
            if (itemView != nullptr) {
                // Нам для получения выпадающего списка надо вызвать edit(),
                // но в документации сказано, что перед ним надо вызвать метод
                // setCurrentIndex() для согласованности
                itemView->setCurrentIndex(index);
                // Вызываем edit для открытия списка
                itemView->edit(index);
            }

            // Сообщаем внешнему вызвавшему этот метод оператору,
            // что инструкция завершилась успешно
            return true;
        }
    }

    // Возвращаем false указав вызвавшему оператору, что событие не обработано
    return false;
}

void ComboBoxDelegate::setData(const QStringList &strList)
{
    // Зададим варианты для вывода в выпадающем списке comboBox
    listOptions = strList;
}

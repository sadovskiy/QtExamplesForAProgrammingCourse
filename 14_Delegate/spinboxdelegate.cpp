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

#include "spinboxdelegate.hpp"

#include <QSpinBox>
#include <QApplication>
#include <QPainter>
#include <QAbstractItemView>

SpinBoxDelegate::SpinBoxDelegate(QWidget *parent):
    QStyledItemDelegate(parent)
{

}

// Создаём виджет редактора значения, который будет использоваться вместо
// стандартного QLineEdit
QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
    // Так как метод переопределяется из базового, мы не можем изменять список
    // его аргументов. Поэтому если часть переменных нами оказалась
    // не задействовано, то что бы компилятор не жаловался
    // на неиспользованные переменные, их можно обернуть в макрос Q_UNUSED()
    Q_UNUSED(option); // или просто объявить, как "(void) option"
    Q_UNUSED(index);

    // Создаём QSpinBox в динамической памяти и передаём
    // указателю editor его адрес.
    // Следует отметить, что для правильной организации объектов
    // им требуется знать, кто родитель "parent"
    QSpinBox *editor = new QSpinBox(parent);

    // Задаём пределы ввода чисел
    // от 0 до 100
    editor->setMinimum(0);
    editor->setMaximum(100);

    // Возвращаем его указатель
    return editor;
}

// Передаём значение от модели QTableWidget в редактор QSpinBox,
// когда пользователь начинает редактирование данных в ячейке таблицы
void SpinBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    // Извлекаем существующие данные, которые находятся в ячейке таблицы
    int value = index.data().toInt();

    // Находим наш динамический QSpinBox созданный в методе createEditor()
    // и получаем указатель на него.
    // Следует заметить, что это надо сделать так,
    // как editor имеет тип QWidget и для правильной работы
    // нам надо его привести к типу QSpinBox. Это делается
    // через специальный шаблон qobject_cast<typename>(object)
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);

    // Помещаем в него значение, находившееся в ячейке
    spinBox->setValue(value);
}

// Передаёт значение от редактора в модель,
// когда пользователь закончил ввод и нажал Enter
void SpinBoxDelegate::setModelData(QWidget *editor,
                                   QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    // Приводим наш spinBox к типу QSpinBox из базового типа QWidget
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);

    // Извлекаем из него значение, которое ввёл пользователь
    int value = spinBox->value();

    // Записываем это значение в ячейку таблицы
    model->setData(index, value);
}

// Задаёт геометрию редактора, то есть, где он будет расположен
// на форме QTableWidget и его размерами
void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    Q_UNUSED(index); // Так как переменная index нам не нужна

    // Указываем, что используемое нами поле ввода должно находится
    // на месте той ячейке, которую мы редактируем
    editor->setGeometry(option.rect);
    // Иначе Qt нарисует его в верхнем левом углу QTableWidget
}

// Данный метод позволяет перерисовать ячейку с нестандартным видом,
// если это требуется разработчику.
// Если же достаточно стандартного вида ячейки, то можно не создавать
// данный метод вообще.
// В нашем случае для примера нарисуем в ячейке индикатор
// выполнения задачи progres bar
void SpinBoxDelegate::paint(QPainter *painter,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{
    // Возьмём значение из ячейки для последующей обработки
    int value = index.data().toInt();

    // Создаём визуальный элемент в виде индикатора хода выполнения
    QStyleOptionProgressBar progressBar;

    // Задаём его свойства
    progressBar.minimum = 0;    // от 0
    progressBar.maximum = 100;  // до 100
    progressBar.rect = option.rect; // Расположение должно быть как в ячейке
    progressBar.progress = value;   // Значение шкалы должно быть как в ячейке
    progressBar.text = QString::number(value); // Дополнительно рядом подписать
    progressBar.textVisible = true; // Включить отображение шкалы

    // Так как мы переопределили метод, отвечающий за рисование ячейки,
    // то пропадут некоторые стандартные свойства, одно из которых
    // это возможность выделять ячейку таблицы.
    // Что бы вернуть эту возможность надо сделать проверку
    // состояния State_Selected текущей ячейки
    if (option.state & QStyle::State_Selected)
        // Делаем её заливку по координатам из option.rect,
        // а цвет берём из текущей политры option.palette
        // подсветки выделенной области highlight()
        painter->fillRect(option.rect, option.palette.highlight());

    // Перерисовываем ячейку в соответствии с новыми правилами оформления
    QApplication::style()->drawControl(QStyle::CE_ProgressBar,
                                       &progressBar,
                                       painter);
}


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

#include "checkboxdelegate.hpp"

#include <QCheckBox>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>

// Методы этого класса работают аналогично методам
// класса SpinBoxDelegate. Всё основное описание находится там.
CheckBoxDelegate::CheckBoxDelegate(QWidget *parent):
    QStyledItemDelegate(parent)
{

}

// Аналогично методу из класса SpinBoxDelegate
QWidget *CheckBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    // Для прекращения получения предупреждений о не используемой переменной
    Q_UNUSED(option); // или (void) option
    Q_UNUSED(index);

    // Создаём объект ввода QCheckBox в динамической памяти и передаём
    // указателю editor его адрес
    QCheckBox *editor = new QCheckBox(parent);

    return editor;
}

// Аналогично методу setEditorData() из класса SpinBoxDelegate
void CheckBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    bool value = index.model()->data(index, Qt::DisplayRole).toBool();

    QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);

    checkBox->setChecked(value);
}

// Аналогично методу setModelData() из класса SpinBoxDelegate
void CheckBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    // Аналогично методу из класса SpinBoxDelegate,
    // но запишем тут в один оператор в место трёх
    model->setData(index,
                   qobject_cast<QCheckBox *>(editor)->isChecked());
}

// Так как обработка нажатия клавиши мыши по ячейке,
// реализованная в методе editorEvent()
// перехватывает фокус раньше, чем срабатывает этот метод,
// то в нашем примере он никогда не запустится при нажатии указателем
// мыши по ячейке. Однако он сработает, при нажатии клавиши пробел если
// ячейка выбрана (выделена). Выбрать ячейку можно перемещаясь
// по таблице с помощью клавиш стрелок на клавиатуре или мышью.
// В случае если бы не было необходимости реализовывать обработку
// действий мыши по ячейке, то метод запускался бы и работал
// аналогично тому, как это происходит в классе SpinBoxDelegate,
// но при тройном нажатии указателем мыши по индикатору CheckBoxIndicator.
// Двойное нажатие для перехода в режим редактирования ячейки и третье
// нажатие для непосредственной отметки индикатора
void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(index);
    // В отличии виджета QSpinBox или используемого по умолчанию QLineEdit,
    // виджет QCheckBox будет не красиво смотреться выровненный по левой
    // стороне столбца. Поэтому лучше его расположение перенести в центр.
    // Для этого создадим объект newEditorOption на основе стилевого
    // класса QStyleOptionButton и изменим некоторые его свойства
    QStyleOptionButton newEditorOption;

    // Создадим временную переменную, отвечающую за расположение виджета ввода,
    // и передадим в неё размеры элемента флага QCheckBox
    QRect rectIndicator =
            QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,
                                                  &newEditorOption);

    // Перенесём координаты текущего расположения существующего элемента
    // в наш временный
    newEditorOption.rect = option.rect;

    // Далее представлен пример как можно изменить месторасположения элемента
    // в ячейке. В примере для понимания расписан алгоритм по шагам
    // с созданием на каждом шаге отдельной переменной.
    // В реальности можно обойтись без переменных
    // и записать всё в один оператор как это показано в методе paint()

    // Получим ширину ячейки по оси x
    // ┌───────────┐
    // │ ▣         │
    // └───────────┘
    //             ↑
    int cellWidth = option.rect.width();

    // Получим середину ячейки
    // ┌───────────┐
    // │ ▣         │
    // └───────────┘
    //       ↑
    int cellCenter = cellWidth / 2;

    // Получим ширину индикатора
    // ┌───────────┐
    // │ ▣         │
    // └───────────┘
    //    ↑
    int CheckIndicatorWidth = rectIndicator.width();

    // Получим середину индикатора
    // ┌───────────┐
    // │ ▣         │
    // └───────────┘
    //   ↑
    int centerOfCheckIndicator = CheckIndicatorWidth / 2;

    // Получим координату точки начала ячейки по оси x в таблице
    // ┌───────────┐
    // │ ▣         │
    // └───────────┘
    // ↑
    int cellX  = option.rect.x();

    // Получим середину ячейки уже относительно таблицы
    // ┌───────────┐
    // │ ▣         │
    // └───────────┘
    //       ↑
    int cellCenterInTable = cellX + cellCenter;

    // Получим начало откуда надо рисовать индикатор относительной таблицы
    // ┌───────────┐
    // │ ▣         │
    // └───────────┘
    //      ↑
    int beginIndicator = cellCenterInTable - centerOfCheckIndicator;

    // Зададим левый край куда надо перерисовать элемент CheckBoxIndicator
    // ┌───────────┐
    // │     ▣     │
    // └───────────┘
    newEditorOption.rect.setLeft(beginIndicator);

    // Задаём новые значения расположения элемента в таблице.
    // После чего он будет перерисован по новым координатам, а значит по центру
    // столбца
    editor->setGeometry(newEditorOption.rect);
}

// Аналогично методу из класса SpinBoxDelegate
void CheckBoxDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    // Обрабатываем прорисовку элемента CheckBoxIndicator с центрированием
    // аналогично подробному описанию выше в методе setModelData()
    QStyleOptionButton newEditorOption;
    QRect rectIndicator =
            QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,
                                                  &newEditorOption);
    newEditorOption.rect = option.rect;
    newEditorOption.rect.setLeft(option.rect.x() +
                                 option.rect.width()/2 -
                                 rectIndicator.width()/2);

    // Конвертируем имеющиеся значение в тип данных bool
    if (index.data().toBool())
        // Если это возможно и значение является истинным (true),
        // то рисуем флажок, через побитовое "ИЛИ" с присвоением
        newEditorOption.state |= QStyle::State_On;
    // Аналогично оператору ↑ полностью можно написать так
    // newEditorOption.state =  .state | QStyle::State_On;

    else
        // Если это возможно, но значение является ложным (false),
        // то стираем флажок QCheckBox
        newEditorOption.state |= QStyle::State_Off;


    // Для сохранения возможности выделения ячейки без её редактирования
    // с использованием побитового "И" проверяем флаг State_Selected
    if (option.state & QStyle::State_Selected)
        // Если он стоит, то оставляем подсветку ячейки в случае выделения мышью
        painter->fillRect(option.rect, option.palette.highlight());

    // Перерисовываем ячейку согласно новым правилам
    QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                       &newEditorOption,
                                       painter);
}

// Метод вызывается при каком-либо событии с ячейкой таблицы.
// Например, нажатием указателя мыши по ячейке или выбором её на клавиатуре,
// или даже просто перемещение указателя мыши над ней
bool CheckBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
    Q_UNUSED(option);
    // Так как метод запускается при любом событии нам надо отфильтровать
    // по такому событию, как отпускание после нажатия указателем мыши
    if (event->type() == QEvent::MouseButtonRelease)
    {
        // Сделаем проверку для реакции только на нажатие по левой кнопки мыши
        if (static_cast<QMouseEvent *>(event)->button() == Qt::LeftButton)
            // Смена состояния флажка QCheckBox
            model->setData(index, !index.data().toBool());

        // Сообщаем внешнему вызвавшему этот метод оператору,
        // что инструкция завершилась успешно
        return true;
    }

    // Возвращаем false указав вызвавшему оператору, что событие не обработано
    return false;
}


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

#include "tablemodel.hpp"

#include <QDebug>
#include <QBrush>


TableModel::TableModel(QObject *parent):
    QAbstractTableModel(parent)
  , columnsNum(3) // Задаём количество столбцов
{
    // Задаём начальные значения в нашу таблицу
    // listStrA — это контейнер для первого столбца
    // listStrB — это контейнер для второго столбца
    for (int i = 0; i < 6; ++i) {
        listStrA.append("Hello " + QString::number(i));
    }
    for (int i = 0; i < 6; ++i) {
        listStrB.append("World " + QString::number(i));
    }

    // А третий столбец заполним текущем временем.
    // Так как тут будет всего одна переменная, то к ней будет обращение
    // из всех ячеек третьего столбца одновременно
    time = QTime::currentTime();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // Установим количество строк в таблице столько же,
    // сколько элементов в списке listStrA
    return listStrA.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // Установим количество столбцов равное трём используя
    // переменную член класса columnsNum
    return columnsNum;
}

// Этот метод вызывается для каждой ячейки и по каждому событию
// для правильной отрисовки объекта и взаимодействия с пользователем
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    // Вытаскиваем текущую строку и столбец
    int row = index.row();
    int col = index.column();

    // Узнаём пустой ли список
    bool valueA = listStrA.at(row).isEmpty();
    bool valueB = listStrB.at(row).isEmpty();

    // Пример для отладки работы метода. Смотреть работу метода через отладчик
    // сложно, так как он вызывается слишком часто по любому событию
    //    qDebug() << QString("row %1, col %2, role %3")
    //                .arg(row).arg(col).arg(role);

    // Работать дальше имеет смысл только при корректном индексе
    if (index.isValid()) {
        // Определяем с какой ролью был вызван метод data(), и что он должен
        // теперь сделать с ячейкой
        switch (role) {
        // Роль, которая отрабатывает, если ячейка отображается в таблице
        case Qt::DisplayRole :
            // Так как поведение для обоих случаев DisplayRole и EditRole
            // одинаковое, то и не надо ставить brake между ними и реализовывать
            // для каждой роли свой набор действий

            // Роль, которая отрабатывает при редактировании ячейки таблицы
        case Qt::EditRole :
            // Для первого столбца извлекаем значение из первого контейнера
            // в соответствии с его строкой
            if (col == 0)
                return listStrA.at(row);
            // Для второго столбца извлекаем значение из первого контейнера
            // в соответствии с его строкой
            if (col == 1)
                return listStrB.at(row);
            // Для третьего столбца извлекаем значение из переменной time.
            // Так как тут нету деления на строки, то значение будет
            // одинаковым для каждой
            if (col == 2)
                return time.toString();
            break;

            // Роль для изменения фона ячейки
        case Qt::BackgroundRole :
            // Для первого столбца
            if (col == 0)
                // и, если ячейка пустая (переменная valueA истинна)
                if (valueA)
                    // она будет закрашена в красный
                    return QBrush(Qt::red);
            // Для второго столбца
            if (col == 1)
                if (valueB)
                    // в зелёный
                    return QBrush(Qt::green);
            // Для третьего
            if (col == 2)
                // закрасить ячейку в цвет морской волны
                return QBrush(Qt::darkCyan);
            // Так как тут нет дополнительных условий, то ячейки всего
            // столбца будут закрашены в этот цвет

            // Для всех остальных случаев выдать недопустимый вариант (invalid)
            return QVariant();

            // Для всех остальных случаев выдать недопустимый вариант (invalid)
        default:
            return QVariant();
        }
    }
    // Для всех остальных случаев выдать недопустимый вариант (invalid)
    else
        return QVariant();
    return QVariant();
}

// Делаем вставку в контейнеры listStrA, listStrB
// введённых пользователем данных в ячейку,
// а в переменную time записываем текущее время
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // Проверим на корректность index
    if (!index.isValid())
        return false;

    // Определяем текущий столбец
    int col = index.column();

    // Определяем текущую роль. Тут почти всегда будет EditRole.
    // Другие роли будут если поменяется поле ввода с текстовой на CheckBox
    if (role == Qt::EditRole) {
        // Если всё хорошо, то определяем какому столбцу относится
        // текущая ячейка и делаем вставку данных в соответствующий
        // контейнер
        if (col == 0)
            listStrA.replace(index.row(), value.toString());
        if (col == 1)
            listStrB.replace(index.row(), value.toString());
        // Для последнего столбца в переменную time вставляем текущее время
        if (col == 2)
            time = QTime::currentTime();
        // Если всё хорошо, то вызывающему методу сообщаем об этом
        return true;
    }

    // Если вставить данные не удалось
    return false;
}

// Задаём заголовки для столбцов и строк таблицы
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Задаём заголовки для столбцов при их отображении
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        // Определяем какой сейчас столбец. Отсчёт идёт от нуля
        switch (section) {
        case 0:
            // Первый столбец называем "A"
            return QString("A");

        case 1:
            // Второй столбец называем "B"
            return QString("B");

        case 2:
            // Третий столбец называем "C"
            return QString("C");
        }
    }

    // Задаём заголовки для строк при их отображении
    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        // Поскольку строки просто нумеруются, можно просто передать значение
        // section + 1 и преобразовать его из int в QString
        return QString::number(section + 1);

    // Для всех остальных случаев выдать недопустимый вариант (invalid)
    return QVariant();
}

// Определяет параметры работы ячейки в таблице
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    // Проверяем на корректность текущий index
    if (index.isValid())
        // Если индекс правильный, то устанавливаем для него
        // следующие стандартные возможности:
        // ItemIsEnabled - включить текущую ячейку;
        // ItemIsSelectable - текущая ячейка может быть выделяемой;
        // ItemIsEditable - текущая ячейка может быть редактируемой;
        // ItemIsDragEnabled - разрешить перемещать данные через захват мышью
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled;
    else
        // Если индекс некорректный, то отправляем нулевой флаг
        return Qt::NoItemFlags;
}

// Слот вставляет новые значения в таблицу
void TableModel::insertValue(const QString &value)
{
    // Тут происходит добавление данных в модель таблицы.
    // Делается это через добавление данных в контейнеры и переменную,
    // а затем обновление модели с уже новыми данными, получаемыми из контейнера
    listStrA << value; // Значение, переданное вызвавшим методом
    listStrB << "new"; // Значение, вставляемое как константа
    // Вставка времени 1:30 как константы в новую строку
    time = QTime::fromString("1.30", "m.s");

    // Данные вставлены в контейнеры и переменную time, но так как модель
    // ничего не знает об этом, надо испустить сигнал layoutChanged() в ручную
    // тем самым заставив модель обновиться
    emit layoutChanged();
}

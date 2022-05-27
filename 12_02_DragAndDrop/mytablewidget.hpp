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

#ifndef MYTABLEWIDGET_HPP
#define MYTABLEWIDGET_HPP

#include <QTableWidget>

// Следует обратить внимание на созданный новый класс MyTableWidget
// Унаследованный от стандартного QTableWidget.
// Его особенность заключается в том,
// что он присутствует на форме mainwindow.ui.
// Делается это следующим образом. Берём визуальный компонент
// наиболее близкий по типу к нашему или являющийся базовым для нашего.
// Размещаем его на форме. Затем нажимаем правой кнопкой указателя мыши
// по этому компоненту и в выпадающем меню выбираем пункт «Преобразовать в …».
// В открывшемся окне выбираем базовый класс, от которого мы наследовались
// и вписываем имя нашего унаследованного класса и имя заголовочного файла,
// где этот класс определён. Если файл имеет такое же имя, что и класс,
// то можно использовать имя файла, вписанное при вводе имени класса.
// После заполнения всех полей надо нажать кнопку добавить
// и наш класс MyTableWidget окажется в списке доступных для использования

class MyTableWidget : public QTableWidget
{
    Q_OBJECT
    // Переменная ответственная за хранение текущего типа MIME,
    // выбираемого пользователем в comboBoxMimeTypeCustomTable
    QString currentMimeType;

    // Определим несколько символов для разметки
    const char cr;        // Возврат каретки (англ. Carriage Return) (Байт: 0x0d)
    const char lf;        // Перевод на строку (англ. Line Feed) (Байт: 0x0a)
    const char tab;       // Табуляция (Байт: 0x09)
    const char comma;     // Запятая (Байт: 0x2C)
    const char semicolon; // Точка с запятой (Байт: 0x3B)
    const char quotes;    // Кавычки (Байт: 0x22)

    // Возможные варианты разделителя столбцов
    char columnDelimiter[3];
    // Текущий разделитель столбцов
    char currentColumnDelimiter;
    // Основные возможные варианты разделителя строк
    char rowDelimiter[3];
    // Текущий основной разделитель строк
    char addCurrentRowDelimiter;
    // Дополнительный символ для переноса из двух символов
    char currentRowDelimiter;
    // Использовать ли кавычки для обрамления данных в ячейке
    bool thereAreQuotes;

    // Определим текущий формат данных MIME
    bool hasFormat(const QString &format) const;

public:
    MyTableWidget(QWidget *parent = nullptr);

protected:
    // Для реализации переноса данных с помощью технологии Drag and Drop
    // ячеек таблицы надо переопределить три метода из класса QTableWidget.
    // Метод mimeData() ответственен за обработку данных ячейки,
    // которую пользователь начал перетаскивать указателем мыши
    QMimeData *mimeData(const QList<QTableWidgetItem *> items) const override;
    // Метод, определяющий типы MIME, которые возможно использовать
    // для переноса ячеек таблицы
    QStringList mimeTypes() const override;
    // Метод, отвечающий за вставку перетаскиваемых данных в нашу таблицу
    bool dropMimeData(int row, int column,
                      const QMimeData *data,
                      Qt::DropAction action) override;

public slots: // Вызов этого метода задаёт использование типа MIME
    void setMimeType(const QString &newMimeType);
    // Устанавливает текущий разделитель для строк
    void setRowDelimiter(int newDelimiter);
    // Устанавливает текущий разделитель для столбцов
    void setColumnDelimiter(int newDelimiter);
    // Устанавливает использование кавычек
    void setQuotes(bool state);

signals:  // Сигнал нужен для установки типа MIME
    void enableDelimiterChange(bool state);
};

#endif // MYTABLEWIDGET_HPP

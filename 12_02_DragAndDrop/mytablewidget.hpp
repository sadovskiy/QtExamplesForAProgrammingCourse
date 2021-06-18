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
// отнаследованный от стандартного QTableWidget.
// Его особенность заключается в том,
// что он присутствует на форме mainwindow.ui.
// Делается это следующим образом. Берём визуальный компонент
// наиболее близкий по типу к нашему или являющийся базовым для нашего.
// Размещаем его на форме. Затем нажимаем правой кнопкой указателя мыши
// по этому компоненту и в выпадающем меню выбираем пункт «Преобразовать в …».
// В открывшемся окне выбираем базовый класс, от которого мы наследовались
// и вписываем имя нашего отнаследованного класса и имя заголовочного файла,
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
    const char cr;        // Возврат каретки (англ. Carriage Return)
    const char lf;        // Перевод на строку (англ. Line Feed)
    const char tab;       // Табуляция
    const char comma;     // Запятая
    const char semicolon; // Точка с запятой
    const char quotes;    // Кавычки

    char columnDelimiter[3];
    short rowDelimiter[3];
    short currentColumnDelimiter;
    char currentRowDelimiter[2];
    bool thereAreQuotes;

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
    void setRowDelimiter(int newDelimiter);
    void setColumnDelimiter(int newDelimiter);
    void setQuotes(bool state);

signals:
    void enableDelimiterChange(bool state);
};

#endif // MYTABLEWIDGET_HPP

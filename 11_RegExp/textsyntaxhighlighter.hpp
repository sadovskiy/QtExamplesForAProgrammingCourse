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

#ifndef TEXTSYNTAXHIGHLIGHTER_HPP
#define TEXTSYNTAXHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>

// Удобным способом работы с поиском посредствам регулярных выражений,
// является работа через подсветку найденных фрагментов текста, а для этого
// необходимое переопределить стандартный класс QSyntaxHighlighter.
// На его основе собственный класс TextSyntaxHighlighter
// управляющий подсветкой
class TextSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    // Создадим переменную член-класса, которая будет хранить
    // шаблон (англ. pattern) поиска
    QString mPattern;

public:
    explicit TextSyntaxHighlighter(QObject *parent = nullptr);

    // Метод, вызывается при изменении текста в документе
    void highlightBlock(const QString &text);

    // Метод, задаёт строку, содержащую шаблон регулярных выражений
    void setPattern(const QString &pattern) {mPattern = pattern;}

signals: // Сигнал, передачи сообщения при ошибке в шаблоне
    void error(const QString &errorMessages, int i);
};

#endif // TEXTSYNTAXHIGHLIGHTER_HPP

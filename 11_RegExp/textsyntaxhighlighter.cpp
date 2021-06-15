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

#include "textsyntaxhighlighter.hpp"

#include <QTextCharFormat>
#include <QRegularExpression>

TextSyntaxHighlighter::TextSyntaxHighlighter(QObject *parent):
    QSyntaxHighlighter(parent)
{

}

// Метод вызывается сам, при любом редактировании текста в plainTextEdit.
// Где он занимается поиском выражения, подпадающего под шаблон mPattern и
// подсвечиванием найденного текста, путём закрашивания фона в серый цвет
void TextSyntaxHighlighter::highlightBlock(const QString &text)
{
    // Проверяем шаблон. Если он пустой,
    // то он пустой и дальнейшие действия не имеют смысла
    if (mPattern.isEmpty())
        return;


    // Создадим объект обработки регулярных выражений и передадим ему
    // шаблон из переменной-члена нашего класса
    QRegularExpression regExp(mPattern);

    // Проверим на корректность выражение (шаблон)
    if (!regExp.isValid()) {

        // Если выражение было не верным есть возможность посмотреть
        // в чём именно была ошибка для этого надо обратится
        // к методу errorString()
        QString errorString = regExp.errorString();

        // Так как сообщения об ошибках выводятся в statusbar главного окна,
        // то нам надо испустить (англ. emit) сигнал и
        // в качестве первого параметра передать сообщение об ошибке,
        // а второго сколько времени оно будет отображаться в миллисекундах.
        // Число 0 означает, что сообщение будет постоянным
        emit error(tr("Expression error: %1").arg(errorString), 0);

        // После вывода сообщения об ошибки, выходим из метода
        return;
    }

    // Создадим объект отвечающий за формат символов в тексте
    QTextCharFormat textFormat;
    // Если ошибок не было, то задаём фон текста серым
    textFormat.setBackground(Qt::gray);

    // Передаём исходный текст объекту regExp для глобального поиска,
    // а в ответ он устанавливает индекс на начало этого текста
    auto index = regExp.globalMatch(text);

    // Начинаем цикл поиска в тексте по шаблону с проверки,
    // есть ли новое выражение для поиска
    while (index.hasNext()) {
        // Если выражение есть, то вытаскиваем его и записываем его в match,
        // а затем переходим к следующему
        auto match = index.next();
        // Узнаем начало и конец найденного выражения match подпадающего под шаблон
        int start = match.capturedStart();
        int end = match.capturedLength();
        // и задаём ему новый формат, с подсветкой в серый фон
        setFormat(start, end, textFormat);
    }
}

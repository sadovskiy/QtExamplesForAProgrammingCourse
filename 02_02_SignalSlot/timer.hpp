/*
 *
 * Copyright (C) 2019 Dept. of Information Systems, Technology and Automation in Construction (ISTAC),
 * Moscow State University of Civil Engineering (MSUCE or MGSU)
 *
 * Written by Sadovskiy B. S.
 *
 *
 * Права на программу (С) 2019 Кафедра информационных систем, технологий и автоматизации в строительстве (ИСТАС),
 * Московский Государственный строительный университет (МГСУ)
 *
 * Написана Садовским Б. С.
 *
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <QObject>


// Создаём класс "Timer", который будет выдавать сигналы в зависимости
// от заданных параметров с определённой переодичностью и количеством.
class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);
    ~Timer();

    // Запуск таймера с количеством циклов "count"
    // и задержками каждого цикла в "ms".
    void start(int count, int ms);

signals:
    // Создаём сигнал, генерируемый на каждом шаге нашего таймера.
    void step(int value);
};

#endif // TIMER_HPP

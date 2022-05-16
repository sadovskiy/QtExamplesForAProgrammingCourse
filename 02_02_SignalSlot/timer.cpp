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

#include "timer.hpp"

/*
 * Так как нам необходима задержка, нам надо подключить заголовочный файл
 * содержащий описание с функцией задержки, но так как они зависят от ОС,
 * то надо их подставлять в зависимости от той ОС, в которой происходит сборка
 * приложения в данный момент.
 */
#ifdef _WIN64
#include <windows.h> // Библиотека для функции задержки в ОС Windows.
#else
#include <unistd.h> // Библиотека для функции задержки в ОС GNU/Linux.
#endif

Timer::Timer(QObject *parent) : QObject(parent)
{

}

Timer::~Timer()
{

}

void Timer::start(const int count, const int delay)
{
    int i = 0;

    // Цикл работает пока не достигнет заданного значения "count".
    while (i <= count) {
        #ifdef _WIN64
        Sleep(delay); // Функция задержки в ОС Windows.
        #else
        usleep(delay); // Функция задержки в ОС GNU/Linux.
        #endif
        // Тут происходит испускание сигнала
        // со значением текущего шага в цикле.
        emit step(i);
        i++;
    }
}

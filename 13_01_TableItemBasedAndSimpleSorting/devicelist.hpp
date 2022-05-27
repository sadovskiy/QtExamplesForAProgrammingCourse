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

#ifndef DEVICELIST_HPP
#define DEVICELIST_HPP

#include "devicelistitem.hpp"

// Для реализации связного списка создадим класс контейнер
class DeviceList
{
    // Данные модели контейнера
    DeviceListItem *first;
    DeviceListItem *last;
    int mCount;

    // Далее методы по манипуляции содержимом модели контейнера
public:
    DeviceList();
    DeviceList(const DeviceList& other);
    ~DeviceList();

    void addDevice(const Device& newDevice);
    void delFirst();
    void delDevice(const int idDevice);
    void delLast();

    int findDevice(const Device& keyDevice) const;
    Device* findDevice(const int idDevice) const;
    Device* findDevice(const std::string &lManufacturer,
                       const std::string &lModel);


    void print(const int idDevice) const;
    void printAll() const;

    bool isEmpty() const;

    int count() const;
};

#endif // DEVICELIST_HPP

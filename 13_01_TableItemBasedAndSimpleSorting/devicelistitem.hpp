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

#ifndef DEVICELISTITEM_HPP
#define DEVICELISTITEM_HPP

#include "device.hpp"

// Для работы со связным списком можно использовать
// наследование и создать из базового класса элемент списка
// добавив указатели на следующий и предыдущий элементы
class DeviceListItem : public Device
{
    // Данные модели списочного элемента
    // Указатели на следующий и предыдущий элемент
    DeviceListItem *mNext;
    DeviceListItem *mPrior;
    // Далее методы по манипуляции моделью списочного элемента
public:
    DeviceListItem();
    DeviceListItem(const int lId,
                   const std::string &lManufacturer,
                   const std::string &lModel);
    explicit DeviceListItem(const Device& dev);

    DeviceListItem(const DeviceListItem& other);

    ~DeviceListItem();

    // Методы для установки текущему элементу адресов следующего
    void setNext(DeviceListItem * const newItem);
    // и предыдущего элементов
    void setPrior(DeviceListItem * const newItem);

    // Методы вернут адреса следующего, предыдущего и текущего элемента
    DeviceListItem *next() const;
    DeviceListItem *prior() const;
    DeviceListItem *current();
};

#endif // DEVICELISTITEM_HPP

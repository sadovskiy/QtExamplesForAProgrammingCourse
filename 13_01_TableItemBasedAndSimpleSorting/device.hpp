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

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>
#include <iostream>

// Пример класса на стандартном С++ позволяет
// создать модель некого объекта, в нашем примере это устройство
class Device
{
    // Данные модели устройства
    // У этого устройства есть три свойства
    int mId; // Уникальный идентификатор
    std::string mManufacturer; // Производитель
    std::string mModel; // Модель устройства

    // Далее методы по манипуляции моделью устройства
public:
    // Стандартные конструкторы, деструктор и операция присваивания
    Device();
    Device(const int lId,
           const std::string &lManufacturer,
           const std::string &lModel);
    Device(const Device &other);

    ~Device();

    Device &operator=(const Device &other);

    // Группа методов для задания новых значений "Геттеры" свойств класса
    void setDevice(const int lId,
                   const std::string &lManufacturer,
                   const std::string &lModel);
    void setID(const int lId);
    void setManufacturer(const std::string &lManufacturer);
    void setModel(const std::string &lModel);

    // Группа методов для получения существующих значений "Сеттеры" свойств класса
    int Id() const;
    std::string manufacturer() const;
    std::string model() const;

    // Методы по выводу данных на терминал командного интерпретатора
    void display() const;
    friend std::ostream &operator<<(std::ostream &os, const Device &dev);
};

#endif // DEVICE_HPP

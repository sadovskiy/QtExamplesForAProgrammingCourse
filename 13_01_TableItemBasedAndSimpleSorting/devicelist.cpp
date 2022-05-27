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

#include "devicelist.hpp"

DeviceList::DeviceList():
    first(nullptr)
  , last(nullptr)
  , mCount(0)
{

}

DeviceList::DeviceList(const DeviceList &other):
    first(nullptr)
  , last(nullptr)
  , mCount(0)
{
    DeviceListItem *current = other.first;
    while (current != nullptr) {
        addDevice(Device(current->Id(),
                         current->manufacturer(),
                         current->model()));
        current = current->next();
    }
}

DeviceList::~DeviceList()
{

}

// // Метод добавляет элементы в конец списка
void DeviceList::addDevice(const Device &newDevice)
{
    // Заводим новый элемент с динамической продолжительностью хранения
    DeviceListItem *newDev = new DeviceListItem(newDevice);
    // Проверяем пустой ли список
    if (first == nullptr)
        // Если список пуст, то объявляем новый элемент первым
        first = newDev;
    else {
        // Если с список не пуст, то добавляем элементы к существующим
        newDev->setPrior(last);
        last->setNext(newDev);
    }

    // Теперь новый элемент стал последним в списке
    last = newDev;

    // Увеличиваем счётчик элементов в контейнере
    mCount++;
}

// Метод удаляет элементы с начала списка
void DeviceList::delFirst()
{
    if (first == nullptr)
        return;
    DeviceListItem *current = first;

    first = first->next();
    first->setPrior(nullptr);

    delete current;
    mCount--;
}

// Метод удаляет элементы с середины списка
void DeviceList::delDevice(const int idDevice)
{
    if (first == nullptr)
        return;
    DeviceListItem *current = first;

    // Прежде чем удалить элемент из середины списка его надо найти
    while (current == first) {
        // В этом примере поиск идёт по уникальному идентификатору устройства
        if (current->Id() == idDevice) {
            // Если элемент удаления найден, то определяем
            // в какой месте списка он находится
            // Удаляем если в начале
            if (current->prior() == nullptr) {
                first = first->next();
                first->setPrior(nullptr);

                delete current;
                mCount--;
                return;
            }
            // Удаляем если в конце
            if (current->next() == nullptr) {
                last = last->prior();
                last->setNext(nullptr);

                delete current;
                mCount--;
                return;
            }
            else {
                // Удаляем если между другими элементами (в середине)
                current->next()->setPrior(current->prior());
                current->prior()->setNext(current->next());

                delete current;
                mCount--;
                return;
            }
        }
        // Переходим к следующему элементу
        current = current->next();
    }

    // Если элементы с запрашиваемым ID не был найден
    std::cout << "Item not found!" << std::endl;
}

// Метод удаляет элементы с конца списка
void DeviceList::delLast()
{
    if (last == nullptr)
        return;
    DeviceListItem *current = last;

    last = last->prior();
    last->setNext(nullptr);

    delete current;
    mCount--;
}

// Метод поиска идентификатора элемента по его адресу
int DeviceList::findDevice(const Device &keyDevice) const
{
    return keyDevice.Id();
}

// Метода поиска адреса элемента по его ID
Device *DeviceList::findDevice(const int idDevice) const
{
    DeviceListItem *current = first;
    while (current != nullptr) {
        if (current->Id() == idDevice)
            return current->current();
        current = current->next();
    }

    // В случае если искомый элемент не был найден
    return nullptr;
}

// Метода поиска адреса элемента по его производителю и модели
Device *DeviceList::findDevice(const std::string &lManufacturer,
                               const std::string &lModel)
{
    DeviceListItem *current = first;
    while (current != nullptr) {
        if (current->manufacturer() == lManufacturer)
            if (current->model() == lModel)
                return current->current();
        current = current->next();
    }

    // В случае если искомый элемент не был найден
    return nullptr;
}

// Метод выводит на консоль объект по ID
void DeviceList::print(const int idDevice) const
{
    findDevice(idDevice)->display();
}

// Метод выводит на консоль весь список объектов
void DeviceList::printAll() const
{
    DeviceListItem *current = first;
    while (current != nullptr) {
        std::cout << current;
        current = current->next();
    }
}

// Метод проверяет есть на пустоту списка
bool DeviceList::isEmpty() const
{
    if (last == nullptr)
        return true;
    else
        return false;
}

// Метод возвращает количество элементов в списке
int DeviceList::count() const
{
    return mCount;
}

#ifndef DEVICELIST_HPP
#define DEVICELIST_HPP

#include "devicelistitem.hpp"

class DeviceList
{
    DeviceListItem *first;
    DeviceListItem *last;
    int mCount;

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

#ifndef DEVICELISTITEM_HPP
#define DEVICELISTITEM_HPP

#include "device.hpp"

class DeviceListItem : public Device
{
    DeviceListItem *mNext;
    DeviceListItem *mPrior;
public:
    DeviceListItem();
    DeviceListItem(const int lId,
                   const std::string &lManufacturer,
                   const std::string &lModel);
    explicit DeviceListItem(const Device& dev);

    DeviceListItem(const DeviceListItem& other);

    ~DeviceListItem();

    void setNext(DeviceListItem * const newItem);
    void setPrior(DeviceListItem * const newItem);

    DeviceListItem *next() const;
    DeviceListItem *prior() const;
    DeviceListItem *current();
};

#endif // DEVICELISTITEM_HPP

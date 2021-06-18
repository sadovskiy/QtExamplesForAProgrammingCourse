#include "devicelistitem.hpp"

DeviceListItem::DeviceListItem():
    Device()
  , mNext(0)
  , mPrior(0)
{

}

DeviceListItem::DeviceListItem(const int lId,
                               const std::string &lManufacturer,
                               const std::string &lModel):
    Device(lId, lManufacturer, lModel)
  , mNext(0)
  , mPrior(0)
{

}

DeviceListItem::DeviceListItem(const Device &dev):
    Device(dev)
  , mNext(0)
  , mPrior(0)
{

}

DeviceListItem::DeviceListItem(const DeviceListItem &other):
    Device(other)
  , mNext(other.mNext)
  , mPrior(other.mPrior)
{

}

DeviceListItem::~DeviceListItem()
{

}

void DeviceListItem::setNext(DeviceListItem * const newItem)
{
    mNext = newItem;
}

void DeviceListItem::setPrior(DeviceListItem * const newItem)
{
    mPrior = newItem;
}

DeviceListItem *DeviceListItem::next() const
{
    return mNext;
}

DeviceListItem *DeviceListItem::prior() const
{
    return mPrior;
}

DeviceListItem *DeviceListItem::current()
{
    return this;
}

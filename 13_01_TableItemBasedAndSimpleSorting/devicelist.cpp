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

void DeviceList::addDevice(const Device &newDevice)
{
    DeviceListItem *newDev = new DeviceListItem(newDevice);
    if (first == nullptr)
        first = newDev;
    else {
        newDev->setPrior(last);
        last->setNext(newDev);
    }

    last = newDev;
    mCount++;
}

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

void DeviceList::delDevice(const int idDevice)
{
    if (first == nullptr)
        return;
    DeviceListItem *current = first;

    while (current== first) {
        if (current->Id() == idDevice) {
            if (current->prior() == nullptr) {
                first = first->next();
                first->setPrior(nullptr);

                delete current;
                mCount--;
                return;
            }
            if (current->next() == nullptr) {
                last = last->prior();
                last->setNext(nullptr);

                delete current;
                mCount--;
                return;
            }
            else {
                current->next()->setPrior(current->prior());
                current->prior()->setNext(current->next());

                delete current;
                mCount--;
                return;
            }
        }
        current = current->next();
    }
    std::cout << "Item not found!" << std::endl;
}

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

int DeviceList::findDevice(const Device &keyDevice) const
{
    return keyDevice.Id();
}

Device *DeviceList::findDevice(const int idDevice) const
{
    DeviceListItem *current = first;
    while (current != nullptr) {
        if (current->Id() == idDevice)
            return current->current();
        current = current->next();
    }
    return nullptr;
}

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
    return nullptr;
}

void DeviceList::print(const int idDevice) const
{
    findDevice(idDevice)->display();
}

void DeviceList::printAll() const
{
    DeviceListItem *current = first;
    while (current != nullptr) {
        std::cout << current;
        current = current->next();
    }
}

bool DeviceList::isEmpty() const
{
    if (last == nullptr)
        return true;
    else
        return false;
}

int DeviceList::count() const
{
    return mCount;
}

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

#include "device.hpp"

Device::Device():
    mId(0)
  , mManufacturer()
  , mModel()
{

}

Device::Device(const int lId,
               const std::string &lManufacturer,
               const std::string &lModel):
    mId(lId)
  , mManufacturer(lManufacturer)
  , mModel(lModel)
{

}

Device::Device(const Device &other):
    mId(other.mId)
  , mManufacturer(other.mManufacturer)
  , mModel(other.mModel)
{

}

Device::~Device()
{

}

Device &Device::operator=(const Device &other)
{
    // Хоть метод и стандартный напомню,
    // что перед копированием полей надо проверить,
    // не присваивает ли метод сам себя
    if (this == &other) return *this;

    mId = other.mId;
    mModel = other.mModel;
    mManufacturer = other.mManufacturer;

    return *this;
}

void Device::setDevice(const int lId,
                       const std::string &lManufacturer,
                       const std::string &lModel)
{
    mId = lId;
    mModel = lModel;
    mManufacturer = lManufacturer;
}

void Device::setID(const int lId)
{
    mId = lId;
}

void Device::setModel(const std::string &lModel)
{
    mModel = lModel;
}

void Device::setManufacturer(const std::string &lManufacturer)
{
    mManufacturer = lManufacturer;
}

int Device::Id() const
{
    return mId;
}

std::string Device::model() const
{
    return mModel;
}

std::string Device::manufacturer() const
{
    return mManufacturer;
}

void Device::display() const
{
    std::cout << "ID: "           << mId    << "\n"
              << "Model: "        << mModel << "\n"
              << "Manufacturer: " << mManufacturer << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Device &dev)
{
    os << "ID: "           << dev.mId    << "\n"
       << "Model: "        << dev.mModel << "\n"
       << "Manufacturer: " << dev.mManufacturer << std::endl;

    return os;
}

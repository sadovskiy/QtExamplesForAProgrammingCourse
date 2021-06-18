#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>
#include <iostream>

class Device
{
    int mId;
    std::string mModel;
    std::string mManufacturer;

public:
    Device();
    Device(const int lId,
           const std::string &lManufacturer,
           const std::string &lModel);
    Device(const Device &other);

    ~Device();

    Device &operator=(const Device &other);

    void setDevice(const int lId,
                   const std::string &lManufacturer,
                   const std::string &lModel);

    void setID(const int lId);
    void setModel(const std::string &lModel);
    void setManufacturer(const std::string &lManufacturer);

    int Id() const;
    std::string model() const;
    std::string manufacturer() const;

    void display() const;
    friend std::ostream &operator<<(std::ostream &os, const Device &dev);
};

#endif // DEVICE_HPP

#include "pcidevice.h"

QString PciDevice::getName() const
{
    return name;
}

void PciDevice::setDeviceID(const QString &value)
{
    deviceID = value;
}

void PciDevice::setVendorID(const QString &value)
{
    vendorID = value;
}

void PciDevice::setName(const QString &value)
{
    name = value;
}

QString PciDevice::getDeviceID() const
{
    return deviceID;
}


QString PciDevice::getVendorID() const
{
    return vendorID;
}

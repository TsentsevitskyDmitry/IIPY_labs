#include "USBDeviceInfo.h"

void USBDeviceInfo::setFlags(unsigned int value)
{
    flags = value;
}

unsigned int USBDeviceInfo::getFlags() const
{
    return flags;
}

void USBDeviceInfo::setDevInst(unsigned int value)
{
    DevInst = value;
}

unsigned int USBDeviceInfo::getDevInst() const
{
    return DevInst;
}

QString USBDeviceInfo::getPidvid() const
{
    return pidvid;
}

void USBDeviceInfo::setDeviceProducer(const QString &value)
{
    deviceProducer = value;
}


void USBDeviceInfo::setDescription(const QString &value)
{
    description = value;
}


void USBDeviceInfo::setFriendlyName(const QString &value)
{
    friendlyName = value;
}

void USBDeviceInfo::setDeviceHardwareId(const QString &value)
{
    deviceHardwareId = value;
    pidvid = value.mid(4, 17);
}

void USBDeviceInfo::setDeviceObjectName(const QString &value)
{
    deviceObjectName = value;
}

bool USBDeviceInfo::ejectSupported()
{
    return (flags & CM_DEVCAP_REMOVABLE);
}

QString USBDeviceInfo::getDeviceHardwareId() const
{
    return deviceHardwareId;
}

QString USBDeviceInfo::getFriendlyName() const
{
    return friendlyName;
}

QString USBDeviceInfo::getDescription() const
{
    return description;
}

QString USBDeviceInfo::getDeviceObjectName() const
{
    return deviceObjectName;
}

QString USBDeviceInfo::getDeviceProducer() const
{
    return deviceProducer;
}

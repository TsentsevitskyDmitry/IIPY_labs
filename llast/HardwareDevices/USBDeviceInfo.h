#ifndef USBDEVICEINFO_H
#define USBDEVICEINFO_H

#include "HardwareDevice.h"
#include <QString>

class USBDeviceInfo : public HardwareDevice
{
protected:
    QString friendlyName;
    QString description;
    QString deviceProducer;
    QString deviceHardwareId;
    QString deviceObjectName;
    QString  pidvid;

    unsigned int flags;
    unsigned int DevInst;

public:
    USBDeviceInfo() :   friendlyName(""),
                        description(""),
                        deviceProducer(""),
                        deviceHardwareId(""),
                        deviceObjectName(""),
                        flags(0),
                        DevInst(0)
    {

    }

    void setDeviceProducer(const QString &value);
    void setDescription(const QString &value);
    void setFriendlyName(const QString &value);
    void setDeviceHardwareId(const QString &value);
    void setDeviceObjectName(const QString &value);
    void setFlags(unsigned int value);
    void setDevInst(unsigned int value);
    bool ejectSupported();

    QString getFriendlyName() const;
    QString getDescription() const;
    QString getDeviceProducer() const;
    QString getDeviceObjectName() const;
    QString getDeviceHardwareId() const;
    unsigned int getFlags() const;
    unsigned int getDevInst() const;
    QString getPidvid() const;
};

#endif // USBDEVICEINFO_H

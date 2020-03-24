#ifndef PCIDEVICE_H
#define PCIDEVICE_H
#include <QString>

class PciDevice
{
private:
    QString name;
    QString vendorID;
    QString deviceID;

public:

    QString getDeviceID() const;
    QString getVendorID() const;
    QString getName() const;
    void setDeviceID(const QString &value);
    void setVendorID(const QString &value);
    void setName(const QString &value);
};

#endif // PCIDEVICE_H

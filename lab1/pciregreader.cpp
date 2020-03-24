#include "pciregreader.h"

QList<PciDevice> PciRegReader::readAll()
{
    QList<PciDevice> devices;

    QSettings m("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Enum\\PCI", QSettings::NativeFormat);
    QStringList pciIDs = m.childGroups();

    foreach (QString id, pciIDs) {
        PciDevice newDevice;

        m.beginGroup(id);
        QString property = m.childGroups()[0];
        QString name = m.value(property.append("/DeviceDesc")).toString();
        m.endGroup();

        PciRegParser::parseIds(newDevice, id);
        PciRegParser::parseName(newDevice, name);

        devices.append(newDevice);
    }

    return devices;
}

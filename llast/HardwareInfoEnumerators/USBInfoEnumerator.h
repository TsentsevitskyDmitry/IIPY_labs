#ifndef USBDEVICES_H
#define USBDEVICES_H

#include "HardwareInfoInterface.h"
#include "HardwareDevices/USBDeviceInfo.h"
#include <windows.h>
#include <setupapi.h>

class USBInfoEnumerator : public HardwareInfoInterface
{
public:
    USBInfoEnumerator();


    void update();
    USBDeviceInfo* operator[](size_t i);
    bool listContain(QString pidvid);
};

#endif // USBDEVICES_H

#ifndef HARDWAREINFOINTERFACE_H
#define HARDWAREINFOINTERFACE_H
#include <vector>
#include "HardwareDevices/HardwareDevice.h"

class HardwareInfoInterface
{
protected:
    size_t devicesCount;
    std::vector<HardwareDevice*> devices;

public:
    HardwareInfoInterface() : devicesCount() {}
    virtual ~HardwareInfoInterface();

    size_t getDevicesCount();
    bool devicesListChanged();

    virtual void update() = 0;
    virtual HardwareDevice* operator[](size_t i) = 0;

};

#endif // HARDWAREINFOINTERFACE_H

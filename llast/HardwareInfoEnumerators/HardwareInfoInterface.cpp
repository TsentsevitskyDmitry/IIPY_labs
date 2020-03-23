#include "HardwareInfoInterface.h"

HardwareInfoInterface::~HardwareInfoInterface()
{
    for(size_t i = 0; i< devices.size(); ++i)
        delete devices[i];
}

size_t HardwareInfoInterface::getDevicesCount()
{
    return devices.size();
}

bool HardwareInfoInterface::devicesListChanged()
{
    update();
    if(devices.size() != devicesCount){
        devicesCount = devices.size();
        return true;
    }
    return false;
}

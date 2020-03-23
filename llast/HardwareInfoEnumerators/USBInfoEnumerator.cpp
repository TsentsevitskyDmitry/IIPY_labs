#include "USBInfoEnumerator.h"
#include <windows.h>
#include <cfgmgr32.h >

USBInfoEnumerator::USBInfoEnumerator()
{

}

void USBInfoEnumerator::update()
{
    // Retrieve the device information set for the interface class.
    HDEVINFO DeviceInfoSet = SetupDiGetClassDevsA(nullptr, "USB", nullptr, DIGCF_ALLCLASSES | DIGCF_PRESENT);

    if(DeviceInfoSet == INVALID_HANDLE_VALUE) {
        printf( "SetupDiGetClassDevsEx failed: %lx.\n", GetLastError() );
        return;
    }

    SP_DEVINFO_DATA DeviceInfoData;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    DWORD i = 0;
    DWORD requiredSize;
    devices.clear();
    while(SetupDiEnumDeviceInfo(DeviceInfoSet, i++, &DeviceInfoData))
    {
        USBDeviceInfo* info = new USBDeviceInfo();
        BYTE propBuffer[512];
        info->setDevInst(DeviceInfoData.DevInst);

        SetupDiGetDeviceRegistryPropertyA(DeviceInfoSet, &DeviceInfoData, SPDRP_MFG, nullptr, propBuffer, 512, &requiredSize);
        info->setDeviceProducer(QString::fromLocal8Bit(reinterpret_cast<char*>(propBuffer)));

        SetupDiGetDeviceRegistryPropertyA(DeviceInfoSet, &DeviceInfoData, SPDRP_FRIENDLYNAME, nullptr, propBuffer, 512, &requiredSize);
        info->setFriendlyName(QString::fromLocal8Bit(reinterpret_cast<char*>(propBuffer)));

        SetupDiGetDeviceRegistryPropertyA(DeviceInfoSet, &DeviceInfoData, SPDRP_HARDWAREID, nullptr, propBuffer, 512, &requiredSize);
        info->setDeviceHardwareId(QString::fromLocal8Bit(reinterpret_cast<char*>(propBuffer)));

        SetupDiGetDeviceRegistryPropertyA(DeviceInfoSet, &DeviceInfoData, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME, nullptr, propBuffer, 512, &requiredSize);
        info->setDeviceObjectName(QString::fromLocal8Bit(reinterpret_cast<char*>(propBuffer)));

        SetupDiGetDeviceRegistryPropertyA(DeviceInfoSet, &DeviceInfoData, SPDRP_DEVICEDESC, nullptr, propBuffer, 512, &requiredSize);
        info->setDescription(QString::fromLocal8Bit(reinterpret_cast<char*>(propBuffer)));

        DWORD flags = 0;
        SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_CAPABILITIES,nullptr, reinterpret_cast<BYTE*>(&flags), 512, &requiredSize);
        info->setFlags(flags);

        if(!listContain(info->getPidvid()))
            devices.push_back(info);
    }


    SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}

bool USBInfoEnumerator::listContain(QString pidvid)
{
    for(size_t i = 0; i < devices.size(); ++i)
        if (static_cast<USBDeviceInfo *>(devices[i])->getPidvid() == pidvid)
            return true;
    return false;
}

USBDeviceInfo *USBInfoEnumerator::operator[](size_t i)
{
    return static_cast<USBDeviceInfo *>(devices[i]);
}

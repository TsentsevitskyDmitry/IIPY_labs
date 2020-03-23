#include "USBService.h"
#include <cfgmgr32.h>
#include <iostream>

void USBService::setRunning(bool state)
{
    running = state;
}

QString USBService::getInStringListData()
{
    QString fakeList;
    removeList.clear();

    for(size_t i= 0; i < devInfo.getDevicesCount(); ++i){
        fakeList += "USB device #" + QString::number(i + 1) + "\n";
        fakeList += "Description: " + devInfo[i]->getDescription() + "\n";
        fakeList += "Name: " + devInfo[i]->getFriendlyName() + "\n";
        fakeList += "Producer: " + devInfo[i]->getDeviceProducer() + "\n";
        fakeList += "HardwareID: " + devInfo[i]->getDeviceHardwareId() + "\n";
        fakeList += "Object Name: " + devInfo[i]->getDeviceObjectName() + "\n";
        fakeList += "devinst: " + QString::number(devInfo[i]->getDevInst()) + "\n";
        fakeList += "\n";

        if(devInfo[i]->getDescription() == "Запоминающее устройство для USB")
            removeList.push_back(devInfo[i]->getDevInst());
    }

    return fakeList;
}

bool USBService::tryToRemove(int pos)
{
    std::cout << "pos: " << pos << " ";
    DWORD devinst = removeList[static_cast<size_t>(pos)];
    std::cout << "try: " << devinst << std::endl;
    return CM_Request_Device_Eject(devinst, nullptr, nullptr, NULL, NULL) == CR_SUCCESS;
}

void USBService::updating()
{
    while(running){
        if(devInfo.devicesListChanged())
            emit needToUpdate();
        QThread::msleep(200);
    }

    emit threadTerminate();
}

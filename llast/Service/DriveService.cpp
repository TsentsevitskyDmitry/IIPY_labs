#include "DriveService.h"
#include <windows.h>


void DriveService::updating()
{
    while(running){
        refresh();
        if(driveList.size() != lastSize){
            lastSize = driveList.size();
            emit needToUpdate();
        }
        QThread::msleep(200);
    }

    emit threadTerminate();
}

void DriveService::refresh()
{
    DWORD logicalDrives = GetLogicalDrives();
    int driveLetter = 0;
    char driveName[4] = {0};
    driveList.clear();

    for(int i = 0; i < BITMASK_LEN; ++i)
    {
        driveLetter = ((logicalDrives >> i) & 0x00000001);
        if(driveLetter){
            driveName[0] = char('A' + i);
            driveName[1] = ':';
            driveName[2] = '\\';

            UINT driveType = GetDriveTypeA(driveName);
            if(driveType != DRIVE_REMOVABLE) continue;
            driveList.push_back(QString(driveName));
        }
    }
}

void DriveService::setRunning(bool state)
{
    running = state;
}

std::list<QString> DriveService::getInStringListData()
{
    return driveList;
}

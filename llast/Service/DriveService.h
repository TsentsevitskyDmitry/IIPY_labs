#ifndef DRIVESERVICE_H
#define DRIVESERVICE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QString>
#include <list>
#include "HardwareDevices/HardwareDevice.h"

#define BITMASK_LEN 24
#define BUFF_SIZE 512

class DriveService : public QObject
{
    Q_OBJECT
private:
    std::list<QString> driveList;
    size_t lastSize;
    bool running;
    void refresh();

public:
    DriveService() : driveList(), lastSize(0), running(false)
    {

    }
    ~DriveService() {}

public slots:
    void setRunning(bool state);
    void updating();
    std::list<QString> getInStringListData();

signals:
    void needToUpdate();
    void threadTerminate();

};

#endif // DRIVESERVICE_H

#ifndef USBSERVICE_H
#define USBSERVICE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <vector>
#include "HardwareInfoEnumerators/USBInfoEnumerator.h"

class USBService : public QObject
{
    Q_OBJECT
private:
    USBInfoEnumerator devInfo;
    std::vector<DWORD> removeList;
    bool running;

public:
    USBService() : devInfo(), removeList(), running(false)
    {

    }
    ~USBService() {}

public slots:
    void setRunning(bool state);
    void updating();
    QString getInStringListData();
    bool tryToRemove(int pos);

signals:
    void needToUpdate();
    void threadTerminate();

};

#endif // USBSERVICE_H

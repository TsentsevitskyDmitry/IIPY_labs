#ifndef PCIREGREADER_H
#define PCIREGREADER_H

#include <QString>
#include <QList>
#include <QSettings>

#include "pcidevice.h"
#include "pciregparser.h"

class PciRegReader
{

public:
    QList<PciDevice> readAll();
};

#endif // PCIREGREADER_H

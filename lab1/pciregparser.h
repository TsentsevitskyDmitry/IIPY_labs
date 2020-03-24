#ifndef PCIREGPARSER_H
#define PCIREGPARSER_H

#include <QString>
#include "pcidevice.h"

class PciRegParser
{
public:
    static void parseIds(PciDevice& device, QString ids);
    static void parseName(PciDevice& device, QString ids);

};

#endif // PCIREGPARSER_H

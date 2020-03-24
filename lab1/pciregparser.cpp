#include <QRegExp>
#include <iostream>
#include "pciregparser.h"

void PciRegParser::parseIds(PciDevice &device, QString ids)
{
    QRegExp rx("DEV_([0-9a-zA-Z])&");
     int pos = rx.indexIn(ids);
     if (pos > -1)
         device.setDeviceID("DEV" + rx.cap(1));

      std::cout << ids.toStdString() << rx.cap(1).toStdString() << std::endl;

     rx.setPattern("VEN_([0-9a-zA-Z])&");
      pos = rx.indexIn(ids);
      if (pos > -1)
          device.setDeviceID("VEN" + rx.cap(1));
}

void PciRegParser::parseName(PciDevice &device, QString ids)
{

}


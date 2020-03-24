#ifndef BYSTYPES_H
#define BYSTYPES_H
#include <QString>
using namespace std;

QString BUS_TYPES[] = {
  "BusTypeUnknown",
  "BusTypeScsi",
  "BusTypeAtapi",
  "BusTypeAta",
  "BusType1394",
  "BusTypeSsa",
  "BusTypeFibre",
  "BusTypeUsb",
  "BusTypeRAID",
  "BusTypeiScsi",
  "BusTypeSas",
  "BusTypeSata",
  "BusTypeSd",
  "BusTypeMmc",
  "BusTypeVirtual",
  "BusTypeFileBackedVirtual",
  "BusTypeSpaces",
  "BusTypeNvme",
  "BusTypeSCM",
  "BusTypeUfs",
  "BusTypeMax",
  "BusTypeMaxReserved"
};

#endif // BYSTYPES_H

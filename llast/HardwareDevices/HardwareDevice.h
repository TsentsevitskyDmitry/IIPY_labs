#ifndef HARDWAREDEVICE_H
#define HARDWAREDEVICE_H

#define CM_DEVCAP_LOCKSUPPORTED (0x00000001)
#define CM_DEVCAP_EJECTSUPPORTED (0x00000002)
#define CM_DEVCAP_REMOVABLE (0x00000004)
#define CM_DEVCAP_DOCKDEVICE (0x00000008)
#define CM_DEVCAP_UNIQUEID (0x00000010)
#define CM_DEVCAP_SILENTINSTALL (0x00000020)
#define CM_DEVCAP_RAWDEVICEOK (0x00000040)
#define CM_DEVCAP_SURPRISEREMOVALOK (0x00000080)
#define CM_DEVCAP_HARDWAREDISABLED (0x00000100)
#define CM_DEVCAP_NONDYNAMIC (0x00000200)

class HardwareDevice
{
public:
    HardwareDevice();
};

#endif // HARDWAREDEVICE_H

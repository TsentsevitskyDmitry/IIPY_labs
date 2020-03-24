#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bustypes.h"
#include <QRegExp>
#include <cstring>
#include <cmath>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < getDiskCount(); ++i)
        ui->comboBox->addItem("Disk drive " + QString::number(i));

    updater = new Updater();
    QThread *thread = new QThread;
    updater->moveToThread(thread);

    connect(thread, SIGNAL(started()), updater, SLOT(process()));
    connect(updater, SIGNAL(update()), this, SLOT(updateInfo()));
    connect(this, SIGNAL(closeUpdater()), updater, SLOT(finished()));
    connect(updater, SIGNAL(end_process()), thread, SLOT(quit()));

    thread->start();
}

MainWindow::~MainWindow()
{
    emit closeUpdater();
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    this->currentIndex = index;

//    this->updateInfo();
}

void MainWindow::updateInfo() {
    ui->textBrowser->clear();
    showHardInfo(currentIndex);
    showSizeInfo(currentIndex);
    showPartInfo(currentIndex);
}

int MainWindow::getDiskCount()
{
    return 1;
}

void MainWindow::showHardInfo(UINT nDriveNumber)
{
    // Format physical drive path (may be '\\.\PhysicalDrive0', '\\.\PhysicalDrive1' and so on).
    string strDrivePath = "\\\\.\\PhysicalDrive";
    strDrivePath.append(QString::number(nDriveNumber).toStdString());

    // call CreateFile to get a handle to physical drive
    HANDLE hDevice = CreateFileA(strDrivePath.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, 0, NULL);

    if(INVALID_HANDLE_VALUE == hDevice)
        return;

    // set the input STORAGE_PROPERTY_QUERY data structure
    STORAGE_PROPERTY_QUERY storagePropertyQuery;
    ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
    storagePropertyQuery.PropertyId = StorageDeviceProperty;
    storagePropertyQuery.QueryType = PropertyStandardQuery;

    // get the necessary output buffer size
    STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
    DWORD dwBytesReturned = 0;
    if(!DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
        &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER),
        &dwBytesReturned, NULL))
        return;


    // allocate the necessary memory for the output buffer
    const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
    char* pOutBuffer = new char[dwOutBufferSize];
    ZeroMemory(pOutBuffer, dwOutBufferSize);

    // get the storage device descriptor
    if (!DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
        &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        pOutBuffer, dwOutBufferSize,
        &dwBytesReturned, NULL))
        return;

    // Now, the output buffer points to a STORAGE_DEVICE_DESCRIPTOR structure
    // followed by additional info like vendor ID, product ID, serial number, and so on.
    STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;

    QString model = QString(pOutBuffer +  pDeviceDescriptor->ProductIdOffset);

    ui->textBrowser->append("Serial Number: " + QString(pOutBuffer +  pDeviceDescriptor->SerialNumberOffset));
    ui->textBrowser->append("Manufactor: " + model.split(" ")[0]);
    ui->textBrowser->append("Model: " + model.split(" ")[1]);
    ui->textBrowser->append("Frimware vrsion: " + QString(pOutBuffer +  pDeviceDescriptor->ProductRevisionOffset));
    ui->textBrowser->append("Bys type: " + BUS_TYPES[pDeviceDescriptor->BusType]);


    // perform cleanup and return
    delete[]pOutBuffer;
    CloseHandle(hDevice);
    return;
}

void MainWindow::showSizeInfo(UINT nDriveNumber)
{
    DISK_GEOMETRY pdg = { 0 }; // disk drive geometry structure
    BOOL bResult = FALSE;      // generic results flag
    ULONGLONG DiskSize = 0;    // size of the drive, in bytes

    string strDrivePath = "\\\\.\\PhysicalDrive";
    strDrivePath.append(QString::number(nDriveNumber).toStdString());
    HANDLE hDevice = INVALID_HANDLE_VALUE;  // handle to the drive to be examined
    DWORD junk     = 0;                     // discard results

    hDevice = CreateFileA(strDrivePath.c_str(),          // drive to open
                          0,                // no access to the drive
                          FILE_SHARE_READ | // share mode
                          FILE_SHARE_WRITE,
                          NULL,             // default security attributes
                          OPEN_EXISTING,    // disposition
                          0,                // file attributes
                          NULL);            // do not copy file attributes

    if (hDevice == INVALID_HANDLE_VALUE)    // cannot open the drive
    {
      return;
    }

    bResult = DeviceIoControl(hDevice,                       // device to be queried
                              IOCTL_DISK_GET_DRIVE_GEOMETRY, // operation to perform
                              NULL, 0,                       // no input buffer
                              &pdg, sizeof(pdg),            // output buffer
                              &junk,                         // # bytes returned
                              (LPOVERLAPPED) NULL);          // synchronous I/O

    CloseHandle(hDevice);

    if (bResult)
    {
        DiskSize = pdg.Cylinders.QuadPart * (ULONG)pdg.TracksPerCylinder *
                   (ULONG)pdg.SectorsPerTrack * (ULONG)pdg.BytesPerSector;
      ui->textBrowser->append("Full disk size = " + QString::number(DiskSize / pow(1024, 3)) + " Gb");
      ui->textBrowser->append("");
    }
}

void MainWindow::showPartInfo(UINT nDriveNumber)
{
    DWORD logicalDrives = GetLogicalDrives();
    int driveLetter = 0;
    char driveName[4] = {0};

    DWORD VolumeSerialNumber;
    char VolumeNameBuffer[BUFF_SIZE];
    char fileSystemNameBuffer[BUFF_SIZE];

    for(int i = 0; i < BITMASK_LEN; ++i)
    {
        driveLetter = ((logicalDrives >> i) & 0x00000001);
        if(driveLetter){
            driveName[0] = char('A' + i);
            driveName[1] = ':';
            driveName[2] = '\\';

            UINT driveType = GetDriveTypeA(driveName);
            if(driveType != DRIVE_FIXED) continue;

            if (!GetVolumeInformationA(
                driveName,
                VolumeNameBuffer,
                BUFF_SIZE,
                &VolumeSerialNumber,
                NULL,
                NULL,
                fileSystemNameBuffer,
                BUFF_SIZE))
            {
                return;
            }

            ULARGE_INTEGER  freeBytesAvailable;
            ULARGE_INTEGER  totalNumberOfBytes;
            ULARGE_INTEGER  totalNumberOfFreeBytes;

            if(!GetDiskFreeSpaceExA(
                driveName,
                &freeBytesAvailable,
                &totalNumberOfBytes,
                &totalNumberOfFreeBytes))
            {
                return;
            }

            double totalSpace = totalNumberOfBytes.QuadPart / pow(1024, 3);
            double freeSpace = totalNumberOfFreeBytes.QuadPart / pow(1024, 3);
            double usedSpace = totalSpace - freeSpace;

            ui->textBrowser->append("Logical drive : " + QString(driveName));
            ui->textBrowser->append("Total size: " + QString::number(totalSpace) + " Gb");
            ui->textBrowser->append("Free space: " + QString::number(freeSpace) + " Gb");
            ui->textBrowser->append("Used space: " + QString::number(usedSpace) + " Gb");
            ui->textBrowser->append("");

        }
    }
}



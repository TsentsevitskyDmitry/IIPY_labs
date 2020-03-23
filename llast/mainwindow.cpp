#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "HardwareInfoEnumerators/USBInfoEnumerator.h"

MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent),
                                            ui(new Ui::MainWindow),
                                            usbService(),
                                            driveService()
{
    ui->setupUi(this);
    // USB
    connect(&usbServiceThread, &QThread::started, &usbService, &USBService::updating);
    connect(&usbService, &USBService::threadTerminate, &usbServiceThread, &QThread::terminate);
    connect(&usbService, &USBService::needToUpdate, this, &MainWindow::updateUSBInfo);
    usbService.moveToThread(&usbServiceThread);

    // Drivers
    connect(&driveServiceThread, &QThread::started, &driveService, &DriveService::updating);
    connect(&driveService, &DriveService::threadTerminate, &driveServiceThread, &QThread::terminate);
    connect(&driveService, &DriveService::needToUpdate, this, &MainWindow::updateDriveInfo);
    driveService.moveToThread(&driveServiceThread);


    usbServiceThread.start();
    usbService.setRunning(true);

    driveServiceThread.start();
    driveService.setRunning(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUSBInfo()
{
    ui->infoBox->clear();
    ui->infoBox->append(usbService.getInStringListData());
}

void MainWindow::updateDriveInfo()
{
    ui->driversCombo->clear();
    ui->driversCombo->addItems(QStringList::fromStdList(driveService.getInStringListData()));
}

void MainWindow::on_updateButton_clicked()
{
    updateUSBInfo();
    updateDriveInfo();
}

void MainWindow::on_ejectButton_clicked()
{
    int pos = ui->driversCombo->currentIndex();
    if(pos < 0) return;

    if (usbService.tryToRemove(pos))
        QMessageBox::information(this, "Успех","Вам это удалось!");
    else
        QMessageBox::warning(this, "Внимание","Диск занят, извлечение невозможно");
}
